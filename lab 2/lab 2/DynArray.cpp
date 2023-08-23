#include "DynArray.h"
#include <iostream>

void DynArr::arrCreate() {
    arr = new int[n];
}

DynArr::DynArr()
: n(0) {
    arrCreate();
}

DynArr::DynArr(int size)
: n(size) {
    arrCreate();
};

void DynArr::addToBeg(const int element) {
    n++;
    int *tempArr = new int[n];

    for (int i = 1; i < n; i++) {
        tempArr[i] = arr[i - 1];
    }

    tempArr[0] = element;
    
    delete [] arr;

    arr = tempArr;

    
}

void DynArr::addToEnd(int element) {
    n++;
    int *tempArr = new int[n];

    for (int i = 0; i < n - 1; i++) {
        tempArr[i] = arr[i];
    }

    delete [] arr;

    arr = tempArr;

    arr[n - 1] = element;
}

void DynArr::delFromBeg() {
    n--;
    int *tempArr = new int[n];

    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[i + 1];
    }

    delete [] arr;

    arr = tempArr;
}

void DynArr::delFromEnd() {
    n--;
    int *tempArr = new int[n];

    for (int i = 0; i < n; i++) {
        tempArr[i] = arr[i];
    }

    delete [] arr;

    arr = tempArr;
}

void DynArr::addToPos(int element, int index) {
    if (index < 0 || index > n) {
        std::cout << "You've entered an incorrect index\n";
    } else {
        n++;
        int *tempArr = new int[n];

        for (int i = 0; i <= index; i++) {
            if (i != index) {
                tempArr[i] = arr[i];
            } else {
                tempArr[i] = element;
            }
        }
        if (n - index > 0) {
            for (int i = index; i < n; i++) {
                tempArr[i + 1] = arr[i];
            }
        }

        delete [] arr;

        arr = tempArr;
    }
}

void DynArr::output() {
    std::cout << "The array is: \n";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << "\t";
    }
    std::cout << "\n";
}

void DynArr::clear() {
    for (int i = 0; i < n; i++) {
        arr[i] = 0;
    }
    n = 0;
}

void DynArr::getSize() {
    std::cout << "The array contains " << n << " elements\n";
}

void DynArr::randFill() {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 101 - 50;
    }
}

void DynArr::manualFill() {
    std::cout << "Input " << n << " numbers: \n";
    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }
}

int& DynArr::operator[] (const int index) {
    return arr[index];
}

