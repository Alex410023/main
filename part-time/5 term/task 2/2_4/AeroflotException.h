#pragma once

#include <stdexcept>
#include <string>

class AeroflotException : public std::exception {
public:
    AeroflotException(const std::string& message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};
