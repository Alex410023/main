#include "App.h"
#include "Time.h"
#include "Queue.h"

#include <iostream>

using namespace std;

// Time functions
void App::workWithTime() {
    Time time;
    bool runAgain_1 = true;
    
    do {
        cout << "Select an action:\n";
        cout << "1 - Increase seconds/minutes/hours value by 1\n";
        cout << "2 - Decrease seconds/minutes/hours value by 1\n";
        cout << "3 - Increase seconds/minutes/hours value by user's value\n";
        cout << "4 - Decrease seconds/minutes/hours value by user's value\n";
        cout << "5 - Print the time instance\n";
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
                ++time;
                break;
            case 2:
                cout << "Input one number to be added:\n";
                --time;
                break;
            case 3:
                time++;
                break;
            case 4:
                time--;
                break;
            case 5:
                time.print();
                break;
            case 6:
                runAgain_1 = false;
                break;
        }
    } while (runAgain_1);
    cout << "The destructor was called.\n\n";
}


// Queue functions
void App::workWithQueue() {
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
        cout << "2 - Add two queues\n";
        cout << "3 - Extract an element from the queue \n";
        cout << "4 - Subtract queues with each other\n";
        cout << "5 - Multiply queues by each other\n";
        cout << "6 - Divide the queue by a number\n";
        cout << "7 - Print queue\n";
        cout << "8 - Exit\n\n";

        int option_2 = 0;
        while (!(cin >> option_2) || (cin.peek() != '\n') || 
            (option_2 < 1) || (option_2 > 8)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }
        Queue resQueue;

        switch (option_2) {
            case 1:
                cout << "Input a value to be added\n";
                int num_1;
                while (!(cin >> num_1) || (cin.peek() != '\n')) {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "You have entered an incorrect number\n";
                }
                queueNum == 1 ? queue_1 += num_1 : queue_2 += num_1;
                break;
            case 2:
                // The resulting size is the size of the larger queue
                (queue_1 + queue_2).print();
                break;
            case 3:
                cout << "Input a value to be deleted\n";  
                int num_2;
                while (!(cin >> num_2) || (cin.peek() != '\n')) {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "You have entered an incorrect number\n";
                }
                queueNum == 1 ? queue_1 = num_2 : queue_2 = num_2;
                break;
            case 4:
                // The resulting size is the size of the larger queue
                (queue_1 - queue_2).print();
                break;
            case 5:
                // The resulting size is the size of the smaller queue
                (queue_1 * queue_2).print();
                break;
            case 6:
                cout << "Input a number for the queue to be divided by\n";
                int num_3;
                while (!(cin >> num_3) || (cin.peek() != '\n')) {
                    cin.clear();
                    while (cin.get() != '\n');
                    cout << "You have entered an incorrect number\n";
                }
                queueNum == 1 ? (queue_1 / num_3).print() : (queue_2 / num_3).print();
                break;
            case 7: 
                queueNum == 1 ? queue_1.print() : queue_2.print();
                break;
            case 8:
                runAgain_2 = false;
                break;
        }
    } while (runAgain_2);
    cout << "The destructor was called.\n\n";
}

// Main functions
void App::mainTask() {
    bool runAgain = true;
    do {
        cout << "Select what to work with:\n";
        cout << "1 - Time\n";
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
                workWithTime();
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
