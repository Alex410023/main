#include "Menu.h"
#include "Date.h"
#include "Queue.h"

#include <iostream>

using namespace std;

// Date functions
void Menu::workWithDate() {
    Date date;
    bool runAgain_1 = true;

    do {
        cout << "Select an action:\n";
        cout << "1 - Increase days/months/years value by 1\n";
        cout << "2 - Decrease days/months/years value by 1\n";
        cout << "3 - Increase days/months/years value by user's value\n";
        cout << "4 - Decrease days/months/years value by user's value\n";
        cout << "5 - Print the date instance\n";
        cout << "6 - Exit\n\n";

        int option_1 = 0;
        while (!(cin >> option_1) || (cin.peek() != '\n') ||
            (option_1 < 1) || (option_1 > 6)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        switch (option_1) {
        case 1:
            ++date;
            break;
        case 2:
            cout << "Input one number to be added:\n";
            --date;
            break;
        case 3:
            date++;
            break;
        case 4:
            date--;
            break;
        case 5:
            date.print();
            break;
        case 6:
            runAgain_1 = false;
            break;
        }
    } while (runAgain_1);
    cout << "The destructor was called.\n\n";
}


// Queue functions
void Menu::workWithQueue() {
    Queue queue_1, queue_2;

    bool runAgain_2 = true;

    do {
        cout << "Choose which queue to interact with (1/2):\n";
        int queueNum = 0;
        while (!(cin >> queueNum) || (cin.peek() != '\n') || (queueNum < 1) || (queueNum > 2)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        cout << "Select an action:\n";
        cout << "1 - Add an element to the queue\n";
        cout << "2 - Multiply the queue by a number\n";
        cout << "3 - Extract an element from the queue \n";
        cout << "4 - Get the copy of the other queue\n";
        cout << "5 - Check if the first queue is equal to the second one\n";
        cout << "6 - Check if the first queue is unequal to the second one\n";
        cout << "7 - Print queue\n";
        cout << "8 - Add numbers to the queue\n";
        cout << "9 - Exit\n\n";

        int option_2 = 0;
        while (!(cin >> option_2) || (cin.peek() != '\n') ||
            (option_2 < 1) || (option_2 > 9)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        switch (option_2) {
        case 1:
            cout << "Input a value to be added\n";
            int num_1;
            while (!(cin >> num_1) || (cin.peek() != '\n')) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "You have entered an incorrect number\n";
            }
            queueNum == 1 ? queue_1 + num_1 : queue_2 + num_1;
            break;
        case 2:
            cout << "Input a number for the queue to be multiplied by\n";
            int num_3;
            while (!(cin >> num_3) || (cin.peek() != '\n')) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "You have entered an incorrect number\n";
            }
            queueNum == 1 ? (queue_1 * num_3).print() : (queue_2 * num_3).print();
            break;
        case 3:
            cout << "Input a value to be deleted\n";
            int num_2;
            while (!(cin >> num_2) || (cin.peek() != '\n')) {
                cin.clear();
                while (cin.get() != '\n');
                cout << "You have entered an incorrect number\n";
            }
            queueNum == 1 ? queue_1 - num_2 : queue_2 - num_2;
            break;
        case 4:
            queueNum == 1 ? queue_1 = queue_2 : queue_2 = queue_1;
            break;
        case 5:
            queue_1 == queue_2 ? (cout << "Queues are identical\n") : 
                (cout << "Queues are not identical\n");
            break;
        case 6:
            queue_1 != queue_2 ? (cout << "Queues are not identical\n") :
                (cout << "Queues are identical\n");
            break;
        case 7:
            queueNum == 1 ? (cout << queue_1 << "\n\n") : (cout << queue_2 << "\n\n");
            break;
        case 8:
            queueNum == 1 ? (cin >> queue_1) : (cin >> queue_2);
            break;
        case 9:
            runAgain_2 = false;
            break;
        }
    } while (runAgain_2);
    cout << "The destructor was called.\n\n";
}

// Main functions
void Menu::mainTask() {
    bool runAgain = true;
    do {
        cout << "Select what to work with:\n";
        cout << "1 - Date\n";
        cout << "2 - Queue\n";
        cout << "3 - Exit\n\n";

        int option = 0;
        while (!(cin >> option) || (cin.peek() != '\n') || (option < 1) || (option > 3)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        switch (option) {
        case 1:
            workWithDate();
            break;
        case 2:
            workWithQueue();
            break;
        case 3:
            runAgain = false;
            break;
        }
    } while (runAgain);
    cout << "Thank you for using the program.\n";
}
