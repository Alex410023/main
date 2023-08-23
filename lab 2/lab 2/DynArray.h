#pragma once
class DynArr {
private:
    int *arr;
    int n;
    void arrCreate();

public:
    DynArr();
    DynArr(int size);
    
    void addToBeg(const int element);
    void addToEnd(const int element);
    void delFromBeg();
    void delFromEnd();
    void addToPos(int element, int index);
    void output();
    void clear();
    void getSize();
    void randFill();
    void manualFill();
    
    int& operator[] (const int index);
};
