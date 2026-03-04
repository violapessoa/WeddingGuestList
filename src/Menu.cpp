/*
 * Menu.cpp
 * Definitions for menu display and menu action handlers.
 */

#include "Menu.h"
#include "GuestListManager.h"
#include "Guest.h"
#include "Utils.h"
#include <iostream>
#include <string>

void displayMenu() {
    std::cout << "\n  ===== Wedding Guest List Manager =====\n"
              << "  1. Add a new guest\n"
              << "  2. Remove a guest by last name\n"
              << "  3. Update RSVP status\n"
              << "  4. Display all guests\n"
              << "  5. Display total number of attendees\n"
              << "  6. Save guest list to file\n"
              << "  7. Load guest list from file\n"
              << "  8. Exit\n"
              << "  =======================================\n";
}

void doAddGuest(GuestListManager& manager) {
    std::string first = readNonEmptyString("  Enter first name: ");
    std::string last = readNonEmptyString("  Enter last name: ");
    bool rsvp = readYesNo("  RSVP confirmed? (y/n): ");
    int numGuests = readPositiveInt("  Number in party (1-20): ", 20);
    manager.addGuest(Guest(first, last, rsvp, numGuests));
    std::cout << "  Guest added successfully.\n";
}

void doRemoveGuest(GuestListManager& manager) {
    if (manager.getGuestCount() == 0) {
        std::cout << "  No guests to remove.\n";
        return;
    }
    std::string last = readNonEmptyString("  Enter last name to remove: ");
    if (manager.removeGuestByLastName(last)) {
        std::cout << "  Guest(s) with that last name removed.\n";
    } else {
        std::cout << "  No guest found with that last name.\n";
    }
}

void doUpdateRsvp(GuestListManager& manager) {
    if (manager.getGuestCount() == 0) {
        std::cout << "  No guests in the list.\n";
        return;
    }
    std::string last = readNonEmptyString("  Enter last name to update: ");
    bool status = readYesNo("  New RSVP status (y/n): ");
    if (manager.updateRsvpByLastName(last, status)) {
        std::cout << "  RSVP updated.\n";
    } else {
        std::cout << "  No guest found with that last name.\n";
    }
}

void doDisplayTotal(GuestListManager& manager) {
    int total = manager.getTotalAttendees();
    std::cout << "\n  Total attendees (including plus-ones): " << total << "\n";
}

void doSaveToFile(GuestListManager& manager) {
    std::cout << "  Enter filename (or press Enter for 'guest_list.txt'): ";
    std::string filename;
    std::getline(std::cin, filename);
    trimString(filename);
    if (filename.empty()) filename = GuestListManager::DEFAULT_FILENAME;
    if (manager.saveToFile(filename)) {
        std::cout << "  Guest list saved to '" << filename << "'.\n";
    }
}

void doLoadFromFile(GuestListManager& manager) {
    std::cout << "  Enter filename (or press Enter for 'guest_list.txt'): ";
    std::string filename;
    std::getline(std::cin, filename);
    trimString(filename);
    if (filename.empty()) filename = GuestListManager::DEFAULT_FILENAME;
    if (manager.loadFromFile(filename)) {
        std::cout << "  Guest list loaded from '" << filename << "'. "
                  << manager.getGuestCount() << " guest(s).\n";
    }
}
