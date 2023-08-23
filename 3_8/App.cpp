#include "App.h"
#include "Queue.h"
#include "Stack.h"

#include <iostream>

using namespace std;

void App::task() {
	Stack stack;
	Queue queue;

    bool runAgain = true;
    do {
        cout << "Select an option:" << endl;
        cout << "1. Push an element to the stack" << endl;
        cout << "2. Pop an element from the stack" << endl;
        cout << "3. Print the stack" << endl;
        cout << "4. Save the stack to a file" << endl;
        cout << "5. Load the stack from a file" << endl;
        cout << "6. Enqueue an element to the queue" << endl;
        cout << "7. Dequeue an element from the queue" << endl;
        cout << "8. Print the queue" << endl;
        cout << "9. Save the queue to a file" << endl;
        cout << "10. Load the queue from a file" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        while (!(cin >> choice) || (cin.peek() != '\n') || 
            (choice < 0) || (choice > 10)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }        cout << endl;

        switch (choice) {
        case 1: {
            int data;
            cout << "Enter the element to push: ";
            cin >> data;
            stack.insert(data);
            break;
        }
        case 2: {
            stack.extract();
            break;
        }
        case 3: {
            cout << "Stack contents: " << endl;
            stack.print();
            break;
        }
        case 4: {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            stack.saveToFile(filename);
            cout << "Stack has been saved to file" << endl << endl;
            break;
        }
        case 5: {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;            
            stack.loadFromFile(filename);
            cout << "Stack has been loaded from file" << endl << endl;
            break;
        }
        case 6: {
            int data;
            cout << "Enter the element to enqueue: ";
            cin >> data;
            queue.insert(data);
            break;
        }
        case 7: 
            queue.extract();
            break;
        case 8: {
            cout << "Queue contents: " << endl;
            queue.print();
            break;
        }
        case 9: {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            queue.saveToFile(filename);
            cout << "Queue has been saved to file" << endl << endl;
            break;
        }
        case 10: {
            string filename;
            cout << "Enter the filename: ";
            cin >> filename;
            queue.loadFromFile(filename);
            cout << "Queue has been loaded from file" << endl << endl;
            break;
        }
        case 0:
            runAgain = false;
            break;
        }
    } while (runAgain);

    cout << "Thank you for using the program." << endl;
}



