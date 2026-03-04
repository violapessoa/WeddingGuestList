/*
 * Utils.cpp
 * Definitions for string and input utility functions.
 */

#include "Utils.h"
#include <iostream>
#include <limits>
#include <cctype>

void trimString(std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        s.clear();
        return;
    }
    size_t end = s.find_last_not_of(" \t\r\n");
    s = s.substr(start, end - start + 1);
}

void toLowerCase(std::string& s) {
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
}

std::string readNonEmptyString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        trimString(value);
        if (!value.empty()) return value;
        std::cout << "  Input cannot be empty. Please try again.\n";
    }
}

int readPositiveInt(const std::string& prompt, int maxVal) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= 1 && value <= maxVal) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  Please enter a number between 1 and " << maxVal << ".\n";
    }
}

bool readYesNo(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        trimString(value);
        toLowerCase(value);
        if (value == "y" || value == "yes" || value == "1") return true;
        if (value == "n" || value == "no" || value == "0") return false;
        std::cout << "  Please enter (y)es or (n)o.\n";
    }
}

void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
