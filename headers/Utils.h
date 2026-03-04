/*
 * Utils.h
 * Utility function declarations for string and input handling.
 */

#ifndef WEDDING_GUEST_LIST_UTILS_H
#define WEDDING_GUEST_LIST_UTILS_H

#include <string>

void trimString(std::string& s);
void toLowerCase(std::string& s);

std::string readNonEmptyString(const std::string& prompt);
int readPositiveInt(const std::string& prompt, int maxVal = 20);
bool readYesNo(const std::string& prompt);
void clearInputStream();

#endif /* WEDDING_GUEST_LIST_UTILS_H */
