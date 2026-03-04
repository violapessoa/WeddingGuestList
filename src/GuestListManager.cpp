/*
 * GuestListManager.cpp
 * Definition of the GuestListManager class.
 */

#include "GuestListManager.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm>

const std::string GuestListManager::DEFAULT_FILENAME = "guest_list.txt";

void GuestListManager::addGuest(const Guest& guest) {
    guests.push_back(guest);
}

size_t GuestListManager::getGuestCount() const {
    return guests.size();
}

bool GuestListManager::removeGuestByLastName(const std::string& lastName) {
    std::string searchName = lastName;
    trimString(searchName);
    toLowerCase(searchName);

    auto it = std::remove_if(guests.begin(), guests.end(),
        [&searchName](const Guest& g) {
            std::string gLast = g.getLastName();
            trimString(gLast);
            toLowerCase(gLast);
            return gLast == searchName;
        });

    if (it != guests.end()) {
        guests.erase(it, guests.end());
        return true;
    }
    return false;
}

bool GuestListManager::updateRsvpByLastName(const std::string& lastName, bool status) {
    std::string searchName = lastName;
    trimString(searchName);
    toLowerCase(searchName);

    for (Guest& g : guests) {
        std::string gLast = g.getLastName();
        trimString(gLast);
        toLowerCase(gLast);
        if (gLast == searchName) {
            g.setRsvpStatus(status);
            return true;
        }
    }
    return false;
}

void GuestListManager::displayAllGuests() const {
    if (guests.empty()) {
        std::cout << "\n  No guests in the list.\n";
        return;
    }
    std::cout << "\n  --- Guest List ---\n";
    for (size_t i = 0; i < guests.size(); ++i) {
        const Guest& g = guests[i];
        std::cout << "  " << (i + 1) << ". " << g.getFirstName() << " " << g.getLastName()
                  << " | RSVP: " << (g.getRsvpStatus() ? "Yes" : "No")
                  << " | Party size: " << g.getNumberOfGuests() << "\n";
    }
    std::cout << "  ------------------\n";
}

int GuestListManager::getTotalAttendees() const {
    int total = 0;
    for (const Guest& g : guests) {
        if (g.getRsvpStatus()) {
            total += g.getNumberOfGuests();
        }
    }
    return total;
}

bool GuestListManager::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "  Error: Could not open file '" << filename << "' for writing.\n";
        return false;
    }
    for (const Guest& g : guests) {
        out << g.getFirstName() << "\n"
            << g.getLastName() << "\n"
            << (g.getRsvpStatus() ? "1" : "0") << "\n"
            << g.getNumberOfGuests() << "\n";
    }
    if (!out) {
        std::cerr << "  Error: Failed while writing to file.\n";
        return false;
    }
    out.close();
    return true;
}

bool GuestListManager::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "  Error: Could not open file '" << filename << "' for reading.\n";
        return false;
    }
    guests.clear();
    std::string first, last, rsvpStr;
    int numGuests;
    while (std::getline(in, first) && std::getline(in, last) &&
           std::getline(in, rsvpStr) && (in >> numGuests)) {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        bool rsvp = (rsvpStr == "1");
        if (numGuests < 1) numGuests = 1;
        guests.push_back(Guest(first, last, rsvp, numGuests));
    }
    in.close();
    return true;
}
