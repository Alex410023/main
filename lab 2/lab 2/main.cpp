#include <iostream>
#include "DynArray.h"
#include "SortFuncs.h"
#include <ctime>
#include <chrono>

using namespace std;

int main(int argc, const char * argv[]) {
    srand(time(NULL));

    cout << "Input array's size: \n";
    int arrSize = 0;
    cin >> arrSize;
    DynArr array(arrSize);

    cout << "Do you want to fill the array randomly (1) or manually (2)? \n";
    int option = 0;
     cin >> option;
    switch (option) {
        case 1:
            array.randFill();
            break;
        case 2:
            array.manualFill();
        default:
            break;
    }

    cout << "Do you want to print the array? (0 - no, otherwise - yes)\n";
    int print = 0;
    cin >> print;
    if (print) {
        array.output();
    }

    bool runAgain = true;

    do {
        cout << "\nThere are 8 functions: \n 1 - adding to the beginning of the array \n 2 - adding to the end of the array \n 3 - deleting from the beginning of the array \n 4 - deleting from the end of the array \n 5 - adding a number inside the array \n 6 - clearing the whole array \n 7 - finding out the size of the array \n 8 - sorting the array \n";
        int opt = 0;
        cin >> opt;
        switch (opt) {
            case 1: {
                cout << "Input the element: \n";
                int elem = 0;
                cin >> elem;
                array.addToBeg(elem);
                arrSize++;
                break;
            }
            case 2: {
                cout << "Input the element:\n";
                int elem_1 = 0;
                cin >> elem_1;
                array.addToEnd(elem_1);
                arrSize++;
                break;
            }
            case 3: {
                cout << "The first element was deleted.\n";
                array.delFromBeg();
                arrSize--;
                break;
            }
            case 4: {
                cout << "The last element was deleted.\n";
                array.delFromEnd();
                arrSize--;
                break;
            }
            case 5: {
                cout << "Input the number you want to add and it's index: \n";
                int elem_2 = 0, index = 0;
                cin >> elem_2 >> index;
                array.addToPos(elem_2, index);
                arrSize++;
                break;
            }
            case 6: {
                array.clear();
                arrSize = 0;
                break;
            }
            case 7: {
                array.getSize();
                break;
            }
            case 8: {
                auto begin = std::chrono::steady_clock::now();

                timSorting(array, arrSize);
                
                auto end = std::chrono::steady_clock::now();
                auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
                cout << "Sorting time: " << elapsed_ms.count() << " ms\n";
                break;
            }
                
            default:
                break;

        }
        cout << "Do you want to print the array? (0 - no, otherwise - yes)\n";
        int print = 0;
        cin >> print;
        if (print) {
            array.output();
        }

        cout << "Do you want to continue working with the array? (0 - no, otherwise - yes)\n";
        int answer = 0;
        cin >> answer;
        if (!answer) {
            runAgain = false;
        }

    } while (runAgain);

    cout << "\nThank you for using the program.\n";
    return 0;
}
