#include <math.h>
#include <iostream>
#include "SortFuncs.h"
#include "DynArray.h"

int getMinrun(int n) {
    int r = 0; // becomes 1 if there is at least 1 non-zero digit among the shifted bits
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}
/* Tim: take the first 6 bits of N, and add 1 if any of the remaining bits are set.
 Returns the minimum length of a run from 32 to 64 so that the len(array)/minrun is less than or equal to a power of 2. */


void insertionSorting(DynArr array, int begIndex, int endIndex) {
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

void binarySearch(DynArr array, int begIndex, int endIndex) {
    int element = array[endIndex];

    int midIndex = 0, left = 0, right = 0;
    left = begIndex;
    right = endIndex;

    while (right - left > 1) {
        midIndex = (right + left) / 2;
        if (element < array[midIndex]) {
            right = midIndex;
        } else {
            left = midIndex;
        }
    }

    for (int i = endIndex; i > right; i--) {
        array[i] = array[i - 1];
    }
    array[right] = element;
}

int numOfRuns (int size, int minRun) {
    int maxNumRuns = 0;
    maxNumRuns = ceil(static_cast<double>(size) / minRun);
    return maxNumRuns;
}

int** splittingIntoRuns(DynArr array, int minRun, int size, int& runs) {
    int runCounter = 0;

    int** runsArr = new int* [runs];
    for (int i = 0; i < runs; i++) {
        runsArr[i] = new int [2];
    }
// runArr[n][0] - index of the first element of run
// runArr[n][1] - length of run

    int curLen = 1;
    int realRunCount = 0;

    for (int i = 0; i < size - 1; ) {
        while (array[i] <= array[i + 1]) {
            curLen++;
            i++;
        }
        if (curLen < minRun) {
            if (size - i > minRun) {
                i += minRun - curLen;
                curLen = minRun;
                insertionSorting(array, runsArr[runCounter][0], runsArr[runCounter][0] + curLen - 1);
                
                runsArr[runCounter + 1][0] = i + 1;
                runsArr[runCounter][1] = curLen;
                
                runCounter++;
                curLen = 1;
                i++;
                realRunCount++;
            } else {
                curLen += size - i - 1;
                i = size;
                insertionSorting(array, runsArr[runCounter][0], runsArr[runCounter][0] + curLen - 1);
                
                runsArr[runCounter][1] = curLen;
                realRunCount++;
            }
            
        } else {
            runsArr[runCounter][1] = curLen;
            runCounter++;
            curLen = 1;
            i++;
            realRunCount++;
        }
    }
    
    runs = realRunCount;

    return runsArr;
}

void runsMerge(int arrNum_1, int arrNum_2, DynArr array, int** runsArr, int& runs) {
    
    // arrNum_1 is for the left subarray and arrNum_2 is for the right subarray
    int* tempArr = new int [runsArr[arrNum_1][1]];
    for (int i = 0; i < runsArr[arrNum_1][1]; i++) {
        tempArr[i] = array[i + runsArr[arrNum_1][0]];
    }
    
    int left = 0, right = 0, arr = 0;
    right = runsArr[arrNum_2][0];
    arr = runsArr[arrNum_1][0];
    while (left < runsArr[arrNum_1][1] && right < runsArr[arrNum_2][0] + runsArr[arrNum_2][1]) {
        if (tempArr[left] < array[right]) {
            array[arr] = tempArr[left];
            left++;
            arr++;
        } else {
            array[arr] = array[right];
            right++;
            arr++;
        }
    }
    
    while (runsArr[arrNum_1][1] - left > 0) {
        array[arr] = tempArr[left];
        arr++;
        left++;
    }
    while (runsArr[arrNum_2][0] + runsArr[arrNum_2][1] - right > 0) {
        array[arr] = array[right];
        arr++;
        right++;
    }
    
    runsArr[arrNum_1][1] += runsArr[arrNum_2][1];
    for (int i = arrNum_1 + 1; i < runs - 1; i++) {
        runsArr[i][0] = runsArr[i + 1][0];
        runsArr[i][1] = runsArr[i + 1][1];
    }
    runs--;
}

void merge(DynArr array, int** runsArr, int& runs) {
    
    int i = 0;
    int sizeX = 0, sizeY = 0, sizeZ = 0;
    while (runs > 2) {
        sizeX = runsArr[i][1];
        sizeY = runsArr[i + 1][1];
        sizeZ = runsArr[i + 2][1];
        if ((sizeZ > sizeX + sizeY) && (sizeY > sizeX)) {
            i++;
        } else {
            if (runsArr[i + 2][1] < runsArr[i][1]) {
                runsMerge(i + 1, i + 2, array, runsArr, runs);
            } else {
                runsMerge(i, i + 1, array, runsArr, runs);
            }
            i = 0;
        }
    }
    if (runs != 1) {
        runsMerge(0, 1, array, runsArr, runs);
    }
}

void timSorting(DynArr array, int size) {
    int minRun = getMinrun(size);
    if (size < 64) {
        insertionSorting(array, 0, size - 1);
        } else {
            int runs = 0;
            runs = numOfRuns(size, minRun);
            int** runsArr;
            runsArr = splittingIntoRuns(array, minRun, size, runs);
            std::cout << "_______" << "\n";
            merge(array, runsArr, runs);
        }
}
