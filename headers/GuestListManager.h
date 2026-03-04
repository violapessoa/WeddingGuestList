/*
 * GuestListManager.h
 * Declaration of the GuestListManager class for the Wedding Guest List Manager.
 */

#ifndef WEDDING_GUEST_LIST_GUEST_LIST_MANAGER_H
#define WEDDING_GUEST_LIST_GUEST_LIST_MANAGER_H

#include "Guest.h"
#include <string>
#include <vector>

class GuestListManager {
private:
    std::vector<Guest> guests;

public:
    static const std::string DEFAULT_FILENAME;

    void addGuest(const Guest& guest);
    bool removeGuestByLastName(const std::string& lastName);
    bool updateRsvpByLastName(const std::string& lastName, bool status);
    void displayAllGuests() const;
    int getTotalAttendees() const;
    bool saveToFile(const std::string& filename = DEFAULT_FILENAME) const;
    bool loadFromFile(const std::string& filename = DEFAULT_FILENAME);
    size_t getGuestCount() const;
};

#endif /* WEDDING_GUEST_LIST_GUEST_LIST_MANAGER_H */
