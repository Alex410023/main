#pragma once

#include <cstdlib>
#include <ctime>
#include <typeinfo>
#include <iostream>
#include <string>

// Filling the array with the chosen data type function
template <typename T>
void fillArrayRandom(T* arr, const int size) {
    for (int i = 0; i < size; i++) {
        int num = rand() % 61 - 30; // values = [-30..30]
        if constexpr (std::is_same_v<T, int>) {
            arr[i] = num;
        }
        else if constexpr (std::is_same_v<T, char>) {
            num = num % 26 + 'a'; // values = [a..Z]
            arr[i] = static_cast<char>(num);
        }
        else if constexpr (std::is_same_v<T, float>) {
            int degree = rand() % 4 * 8 + 1; // degree = [1..32]
            arr[i] = static_cast<float>(num) / static_cast<float>(pow(2.0, degree));
        }
        else if constexpr (std::is_same_v<T, double>) {
            int degree = rand() % 8 * 8 + 1;
            arr[i] = static_cast<double>(num) / static_cast<double>(pow(2.0, degree));
        }
        else if constexpr (std::is_same_v<T, char*>) {
            const char* characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            const int charCount = strlen(characters);

            int strLength = rand() % 10 + 1; // Random length of the string [1..10]
            arr[i] = new char[strLength + 1]; // Allocate memory for the character array

            for (int j = 0; j < strLength; j++) {
                arr[i][j] = characters[rand() % charCount]; // Fill the character array 
                                                            // with random characters
            }
            arr[i][strLength] = '\0'; // Null-terminate the character array
        }
    }
}

// Array printing function
template <typename T>
void printArray(const T* arr, const int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// Array inversion function
template <typename T>
void arrayInversion(T* arr, const int size) {
    for (int i = 0; i < size / 2; i++) {
        T temp = arr[i];
        arr[i] = arr[size - i - 1];
        arr[size - i - 1] = temp;
    }
}