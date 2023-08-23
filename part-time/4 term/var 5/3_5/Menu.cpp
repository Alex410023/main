#include "Menu.h"
#include "Ball.h"
#include "Tetrahedron.h"
#include "Parallelepiped.h"

#include <iostream>
#include <fstream>

using namespace std;

void Menu::mainMenu() {

    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cout << "Error: could not open file.\n";
    }

    int size;
    cout << "Enter the number of figures you want to create: ";
    cin >> size;

    Shape** shapes = new Shape * [size]; // Array of pointers to Shape objects

    for (int i = 0; i < size; i++) {
        cout << "\nChoose the shape:\n";
        cout << "1. Parallelepiped\n";
        cout << "2. Tetrahedron\n";
        cout << "3. Ball\n";

        int choice;
        while (!(cin >> choice) || (cin.peek() != '\n') ||
            (choice < 1) || (choice > 3)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        int getDataFrom;
        cout << "Do you want to get the data from a file(1) or add it manually(2)? ";
        while (!(cin >> getDataFrom) || (cin.peek() != '\n') ||
            (getDataFrom < 1) || (getDataFrom > 2)) {
            cin.clear();
            while (cin.get() != '\n');
            cout << "You have entered an incorrect number\n";
        }

        if (choice == 1) {
            double length = 0.0, width = 0.0, height = 0.0;
            if (getDataFrom == 1) {
                fin >> length >> width >> height;
            }
            else {
                cout << "Enter the length, width and height: ";
                cin >> length >> width >> height;
            }
            shapes[i] = new Parallelepiped(length, width, height);
        }
        if (choice == 2) {
            double edge = 0.0;
            if (getDataFrom == 1) {
                fin >> edge;
            }
            else {
                cout << "Enter the edge length: ";
                cin >> edge;
            }
            shapes[i] = new Tetrahedron(edge);
        }
        if (choice == 3) {
            double radius = 0.0;
            if (getDataFrom == 1) {
                fin >> radius;
            }
            else {
                cout << "Enter the radius: ";
                cin >> radius;
            }
            shapes[i] = new Ball(radius);
        }
    }
    fin.close();

    // Writing data to a file
    ofstream fout("output.txt");
    if (!fout.is_open()) {
        cout << "Error: could not open file.\n";
        return;
    }

    for (int i = 0; i < size; i++) {
        fout << shapes[i]->surface_area() << "\n";
    }

    fout.close();


    // Deallocating memory
    for (int i = 0; i < size; i++) {
        delete shapes[i];
    }
    delete[] shapes;

    // Reading data from a file
    ifstream fIn("output.txt");
    if (!fIn.is_open()) {
        cout << "Error: could not open file.\n";
    }

    cout << "\nData from file:\n";
    double area;
    for (int i = 0; i < size; i++) {
        fIn >> area;
        cout << "Shape " << i + 1 << ": surface area = " << area << "\n";
    }

    fIn.close();
}
