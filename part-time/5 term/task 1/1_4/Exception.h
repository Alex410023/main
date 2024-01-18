#pragma once

#include <iostream>
#include <string>
#include <stdexcept>

// Define custom exception class
class InputValidationException : public std::exception {
public:
    InputValidationException(const std::string& message) : msg(message) {}

    const char* what() const noexcept override {
        return msg.c_str();
    }

private:
    std::string msg;
};

