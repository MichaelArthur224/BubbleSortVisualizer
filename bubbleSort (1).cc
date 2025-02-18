#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#define MIN_LEN 3
#define MAX_LEN 8
#define SPLIT_CHAR ' ' // Split string by space

using namespace std;

[[ nodiscard ]] string trim(const string& str) noexcept { // Trim spaces of a string.
    string::size_type pos = str.find_first_not_of(' ');
    if (pos == string::npos) {  // If no space found
        return str;
    }
    string::size_type pos2 = str.find_last_not_of(' ');
    if (pos2 != string::npos)
        // Substr starts at first character which is not space
        // Characters num：pos2 - pos + 1
        return str.substr(pos, pos2 - pos + 1);                                         
    return str.substr(pos);
}


[[ nodiscard ]] bool stringSplitToArrayInt(string const&str, char const& split, int &len, vector<int> & array) noexcept {
    if (str.empty()) {
        cout << "\033[0m\033[101m\033[37m" << "I can't do a sort if there is no input.\033[0m\n";
        return false;
    }
    len = 0;                // Length of inputs num
	istringstream iss(str);	// Input stream
	string input;			// Cache area
    int input_num;          // Every inputed num
	while (getline(iss, input, split))	// split string by "split"
	{
        // Discard every space character.
        if (input.find_first_not_of(' ') == string::npos) continue;

        ++len;
        if (len > MAX_LEN) { // Beyond max size
            cout << "\033[0m\033[101m\033[37m" << "The maximum input size is " << MAX_LEN << "\033[0m\n";
            return false;
        }
        try {
            input_num = stoi(input); // Change string type to int type.
        } catch(invalid_argument const& ex) { // Invalid input
            cout << "\033[0m\033[101m\033[37m" << "Please only input numbers.\033[0m\n";
            return false;
        }
        array.push_back(input_num);
	}
    if (len < 3) { // Under min size
        cout << "\033[0m\033[101m\033[37m" << "The minimum input size is " << MIN_LEN << "\033[0m\n";
        array.clear();
        return false;
    }
    return true;
}

void printArray(vector<int> const& array, int const& sorted) noexcept {
    for (int i = 0; i < array.size(); ++i) {
        if (i < sorted) { // Sorted item(s) is(are) red and bold
            cout << "\033[0m\033[31m\033[1m" << array[i] << "\033[0m" << " ";
        } else {
            cout << "\033[0m\033[4m" << array[i];
            if (i != array.size() - 1)
                cout << " ";
        }
    }
}

void printInStepArray(vector<int> const& array, int sorted, int left, int right) noexcept {
    for (int i = 0; i < array.size(); ++i) {
        if (i < sorted) { // Sorted item(s) is(are) red and bold
            cout << "\033[0m\033[1m\033[31m" << array[i] << "\033[0m" << " ";
        } else if (i == left) { // Item compered with has underline
            cout << "\033[0m\033[4m" << array[i] << " ";
        } else if (i == right) { // Item under chaecking is bold with underline
            cout << "\033[0m\033[1m\033[4m" << array[i];
            if (i != array.size() - 1)
                cout << "\033[0m" << " ";
        } else {
            cout << "\033[0m" << array[i] << " ";
        }
    }
    cout << endl;
}

void printBeforeDeterminedArray(vector<int> const& array, int const& sorted, int const& determin) noexcept {
    for (int i = 0; i < array.size(); ++i) {
        if (i < sorted) { // Sorted item(s) is(are) red and bold
            cout << "\033[0m\033[1m\033[31m" << array[i] << "\033[0m" << " ";
        } else if (i >= sorted && i < determin) { // Item(s) determined in this circle is(are) bold
            // Because the last circle will determin 2 items.
            cout << "\033[0m\033[1m" << array[i] << "\033[0m" << " ";
        } 
        else {
            cout << "\033[0m" << array[i] << " ";
        }
    }
    cout << endl;
}

int main() {
    cout << "Bubble Sort\nContributors: Zhenkui Wang, Timothy Wiratmo, Kacy Lam, Henry Hai Nguyen, Michael Arthur\n";

    string input; 
    int input_len = 0;
    vector<int> array_to_sort;

    cout << "Input Array: ";
    getline(cin, input); // Get users input.
    input = trim(input);

    while (input != "quit") {
        if (stringSplitToArrayInt(input, SPLIT_CHAR, input_len, array_to_sort)) {
            cout << "Press any key to start.";
            getchar();
            cout << "***************  Start Sorting  ***************\n\n";
            
            for (int i = 0; i < input_len - 1; ++i) {
                
                printArray(array_to_sort, i);
                cout << "\033[0m" << "   [underlined: unsorted array under sorting]" << endl;

                for (int j = input_len - 1; j > i; --j) { // Check from tail to front.
                    printInStepArray(array_to_sort, i, j - 1, j); // Print current array
                    if (array_to_sort[j] < array_to_sort[j - 1]) 
                        swap(array_to_sort[j], array_to_sort[j - 1]);
                }

                // If this is last circle, argument "determin" should be "input_len"
                printBeforeDeterminedArray(array_to_sort, i, (i == input_len - 2) ? input_len:i + 1);

                cout << "\033[0m" << "Circle " << i + 1 << " of sorting is completed. Press any key to continue";
                getchar();
                cout << "\n";
            }
            cout << "****************  End Sorting  ****************\n\n";
            cout << "\nResult:\n\n";
            printArray(array_to_sort, input_len);
            
            cout << "\n\n\033[0m" << "Sorting completed. Press any key to continue"; 
            getchar();
            cout << endl;
        }

        array_to_sort.clear(); // No matter the input is valid or not, reset array and input_len
        input_len = 0;
        
        cout << "\033[0m" <<"Input Array: ";
        getline(cin, input);
        input = trim(input);
    }

    cout << "\033[0m" << "Bye," << "press any key to quit"; // Byebye.
    getchar();

    return 0;
}