#pragma once

#include <iostream>
#include <iomanip>
#include <cstring>  // For strlen
#include <cmath>    // For pow function
#include <limits>   // For CHAR_MAX
#include <type_traits>  // For type traits

template <typename T>
bool linearSearch(const T* arr, const int size, const T value) {
    for (int i = 0; i < size; i++) {
        if constexpr (std::is_same_v<T, char*>) { // To handle char* values
            if (strcmp(arr[i], value) == 0) {
                return true;
            }
        }
        else {
            if (arr[i] == value) {
                return true;
            }
        }
    }

    return false;  // Indicate value not found
}

template <typename T>
void fillArray(T* arr, const int size) {
    for (int i = 0; i < size; i++) {
        int num = rand() % 201 - 100; // values = [-100..100]
        if constexpr (std::is_same_v<T, int>) {
            arr[i] = num;
        }
        else if constexpr (std::is_same_v<T, char>) {
            num = num % 26 + 'A'; // values = [A..Z]
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

template <typename T>
void printArray(const T* arr, const int size) {
    for (int i = 0; i < size; i++) {
        if constexpr (std::is_same_v<T, float>) {
            std::fixed; 
            std::setprecision(7); // Set precision to 7 digits after the 
                                  //decimal point for float type
        }
        else if constexpr (std::is_same_v<T, double>) {
            std::fixed;
            std::setprecision(10); // Set precision to 10 digits after the 
                                   //decimal point for double type
        }
        std::cout << arr[i] << " ";
        std::cout << std::defaultfloat; // Reset the precision to default

    }
    std::cout << std::endl;
}