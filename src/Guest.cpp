/*
 * Guest.cpp
 * Definition of the Guest class.
 */

#include "Guest.h"

Guest::Guest()
    : firstName(""), lastName(""), rsvpStatus(false), numberOfGuests(1) {}

Guest::Guest(const std::string& first, const std::string& last,
             bool rsvp, int numGuests)
    : firstName(first), lastName(last), rsvpStatus(rsvp), numberOfGuests(numGuests) {}

std::string Guest::getFirstName() const {
    return firstName;
}

std::string Guest::getLastName() const {
    return lastName;
}

bool Guest::getRsvpStatus() const {
    return rsvpStatus;
}

int Guest::getNumberOfGuests() const {
    return numberOfGuests;
}

void Guest::setFirstName(const std::string& first) {
    firstName = first;
}

void Guest::setLastName(const std::string& last) {
    lastName = last;
}

void Guest::setRsvpStatus(bool status) {
    rsvpStatus = status;
}

void Guest::setNumberOfGuests(int num) {
    numberOfGuests = num;
}
