#pragma once
#include "DynArray.h"

int getMinrun(int n);
void insertionSorting(DynArr array, int begIndex, int endIndex);
void binarySearch(DynArr array, int begIndex, int endIndex);
int numOfRuns (int size, int minRun);
int** splittingIntoRuns(DynArr array, int minRun, int size, int& runs);
void runsMerge(int arrNum_1, int arrNum_2, DynArr array, int** runsArr, int& runs);
void runsMerge(int arrNum_1, int arrNum_2, DynArr array, int** runsArr, int& runs);
void merge(DynArr array, int** runsArr, int& runs);
void timSorting(DynArr array, int size);
