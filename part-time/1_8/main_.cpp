/*
	task 1_8
	Finding the last item that is less than the arithmetic mean
*/

#include <iostream>

#include "MainFuncs.h"
#include "Queue1.h"

using namespace std;

int main(int argc, const char* argv[]) {
    Queue1 queue1;
    Queue1 queue1Copy;
    bool exit = false;

    do {
        cout << "Select an action:\n";
        cout << "1 - Push to the queue\n";
        cout << "2 - Delete from the queue\n";
        cout << "3 - Queue output\n";
        cout << "4 - Execute task\n";
        cout << "5 - Create a copy of the queue\n";
        cout << "6 - Merge two queues\n";
        cout << "7 - Exit\n\n";
        int option = 0;

        // The following number input excludes inappropriate symbols
        while (!(cin >> option) || (cin.peek() != '\n') || (option < 1) || (option > 7))
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect symbol(-s)\n";
        }

        switch (option) {
        case 1:
            cout << "Input a number: ";
            int num;
            while (!(cin >> num) || (cin.peek() != '\n'))
            {
                cin.clear();
                while (cin.get() != '\n');
                cout << "You have entered an incorrect number\n";
            }
            queue1.push(num);
            //queue1.plug_push(num);
            break;
        case 2:
            queue1.pop();
            //queue1.plug_pop();
            break;
        case 3:
            print(queue1);
            break;
        case 4:
            task(queue1);
            break;
        case 5:
            copy(queue1, queue1Copy);
            break;
        case 6:
            merge(queue1, queue1Copy);
            break;
        case 7:
            exit = true;
            break;
        }
        cout << "\n";
    } while (!exit);
    cout << "The program has been completed successfully.\n";
}