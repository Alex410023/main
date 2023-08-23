#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

bool correctBrackets(string str) {
    if (str[0] != '(' || str[str.length() - 1] != ')') {
        return false;
    }
    
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if ((count < 0) || ((count == 0 && i < str.length() - 1) && i > 0)) { 
            return false;
        }
        if (str[i] == '(') {
            count++;
        } else if (str[i] == ')') {
            count --;
        }
    }
    
    if (count == 0) {
        return true;
    } else {
        return false;
    }
}

bool correctSymbols(string str) {
    for (int i = 0; i < strlen(str.c_str()); i++) {
        if ((str[i] < 48 || str[i] > 57) && (str[i] != '(' && str[i] != ')') && str[i] != '-') {
            return false;
        }
    }
    return true;
}


void insertionSort(int *array, int begIndex, int endIndex) {
    for (int i = begIndex + 1; i <= endIndex; i++) {
        int temp = array[i];
        int j = i - 1;
        while (j >= begIndex && array[j] > temp) {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = temp;
    }
}

bool hasMoreSons(int *heightsArr, int heightNum) {
    int leftBorder = 0;
    for (int i = 0; i < heightNum; ) {
        leftBorder = i;
        while (heightsArr[i] == heightsArr[i + 1]) {
            i++;
        }
        
        if (i - leftBorder >= 2) {
            return false;
        }
        i++;
    }
    return true;
}

bool isBinaryTree(string str) {
    int height = 1;
    int *heightsArr = (int *)malloc(sizeof(int) * str.length()); // The array containing heights
    int heightNum = 0; // The number of the height
    
    heightsArr[0] = 1;
    for (int i = 1; i < str.length(); ) {
        if (str[i] == '(') {
            height++;
            i++;
        } else if (str[i] == ')') {
            height--;
            i++;
        } else {
            heightsArr[heightNum] = height;
            heightNum++;
            while (str[i] != '(' && str[i] != ')') {
                i++;
            }
        }
    }
    
    heightsArr = (int *)realloc(heightsArr, sizeof(int) * heightNum);
    
    for (int i = 0; i < heightNum; i++) {
        cout << heightsArr[i] << "\t";
    }
    cout << "- unsorted heights\n\n";
    
    
    // Checks if there are "empty" levels
    for (int i = 0; i < heightNum - 1; i++) {
        if (heightsArr[i] + 1 < heightsArr[i + 1]) {
            return false;
        }
    }
    
    // Checks if there are more than 2 sons
    if(!hasMoreSons(heightsArr, heightNum)) {
        return false;
    }
    
    insertionSort(heightsArr, 0, heightNum - 1);

//    for (int i = 0; i < heightNum; i++) {
//        cout << heightsArr[i] << "\t";
//    }
//    cout << "- sorted heights\n";
    
    // Checks if there are more heights than it's possible on a certain level
    if (heightNum > 3) { // The number of heights
        for (int i = 0; i < heightNum - 2; i++) {
            int k = pow(2, heightsArr[i] - 1);
            if (heightsArr[i] == heightsArr[i + k]) {
                return false;
            }
        }
    }
    
    free(heightsArr);
    
    return true;
}


bool parsingIsPossible() {
    ifstream fin;
    fin.open("txts//brackets_input.txt");
    if (!fin.is_open()) {
        cout << "File has not been opened.\n";
        return false;
    }
    
    
    string str;
    getline(fin, str);
    cout << "\n" << str << "\n\n";
    
    if (correctBrackets(str)) {
//        cout << "Correct brackets\n";
        if (correctSymbols(str)) {
//            cout << "Correct symbols\n";
            if (isBinaryTree(str)) {
//                cout << "This is a binary tree\n\n";
            } else {
                cout << "This is not a binary tree\n";
                return false;
            }
        } else {
            cout << "Inorrect symbols\n";
            return false;
        }
    } else {
        cout << "Incorrect brackets\n";
        return false;
    }
    
    cout << "This is a binary tree.\n";

    fin.close();
    return true;
}



//const char keywords[KEYWORDS_NUMBER][9] = {
//    "auto",
//    "break",
//    "case",
//    "char",
//    "const",
//    "continue",
//    "default",
//    "do",
//    "double",
//    "else",
//    "enum",
//    "extern",
//    "float",
//    "for",
//    "goto",
//    "if",
//    "inline",
//    "int",
//    "long",
//    "register",
//    "restrict",
//    "return",
//    "short",
//    "signed",
//    "sizeof",
//    "static",
//    "struct",
//    "switch",
//    "typedef",
//    "union",
//    "unsigned",
//    "void",
//    "volatile",
//    "while"
//};
