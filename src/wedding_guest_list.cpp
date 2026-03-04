/*
 * Wedding Guest List Manager
 * A console application for managing wedding guest lists with file persistence.
 */

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <algorithm>
#include <cctype>

// ============================================================================
// Guest Class
// ============================================================================

class Guest {
private:
    std::string firstName;
    std::string lastName;
    bool rsvpStatus;
    int numberOfGuests;

public:
    // Default constructor
    Guest()
        : firstName(""), lastName(""), rsvpStatus(false), numberOfGuests(1) {}

    // Parameterized constructor
    Guest(const std::string& first, const std::string& last,
          bool rsvp = false, int numGuests = 1)
        : firstName(first), lastName(last), rsvpStatus(rsvp), numberOfGuests(numGuests) {}

    // Getters
    std::string getFirstName() const { return firstName; }
    std::string getLastName() const { return lastName; }
    bool getRsvpStatus() const { return rsvpStatus; }
    int getNumberOfGuests() const { return numberOfGuests; }

    // Setters
    void setFirstName(const std::string& first) { firstName = first; }
    void setLastName(const std::string& last) { lastName = last; }
    void setRsvpStatus(bool status) { rsvpStatus = status; }
    void setNumberOfGuests(int num) { numberOfGuests = num; }
};

// Forward declarations for utilities used by GuestListManager
static void trimString(std::string& s);
static void toLowerCase(std::string& s);

// ============================================================================
// Guest List Manager
// ============================================================================

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
    size_t getGuestCount() const { return guests.size(); }
};

const std::string GuestListManager::DEFAULT_FILENAME = "guest_list.txt";

void GuestListManager::addGuest(const Guest& guest) {
    guests.push_back(guest);
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

// ============================================================================
// Utility Functions (forward declarations used in GuestListManager)
// ============================================================================

static void trimString(std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) {
        s.clear();
        return;
    }
    size_t end = s.find_last_not_of(" \t\r\n");
    s = s.substr(start, end - start + 1);
}

static void toLowerCase(std::string& s) {
    for (char& c : s) {
        c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
}

// ============================================================================
// Input Validation and Menu Helpers
// ============================================================================

static std::string readNonEmptyString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        trimString(value);
        if (!value.empty()) return value;
        std::cout << "  Input cannot be empty. Please try again.\n";
    }
}

static int readPositiveInt(const std::string& prompt, int maxVal = 20) {
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

static bool readYesNo(const std::string& prompt) {
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

static void clearInputStream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void displayMenu() {
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

static void doAddGuest(GuestListManager& manager) {
    std::string first = readNonEmptyString("  Enter first name: ");
    std::string last = readNonEmptyString("  Enter last name: ");
    bool rsvp = readYesNo("  RSVP confirmed? (y/n): ");
    int numGuests = readPositiveInt("  Number in party (1-20): ", 20);
    manager.addGuest(Guest(first, last, rsvp, numGuests));
    std::cout << "  Guest added successfully.\n";
}

static void doRemoveGuest(GuestListManager& manager) {
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

static void doUpdateRsvp(GuestListManager& manager) {
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

static void doDisplayTotal(GuestListManager& manager) {
    int total = manager.getTotalAttendees();
    std::cout << "\n  Total attendees (including plus-ones): " << total << "\n";
}

static void doSaveToFile(GuestListManager& manager) {
    std::cout << "  Enter filename (or press Enter for 'guest_list.txt'): ";
    std::string filename;
    std::getline(std::cin, filename);
    trimString(filename);
    if (filename.empty()) filename = GuestListManager::DEFAULT_FILENAME;
    if (manager.saveToFile(filename)) {
        std::cout << "  Guest list saved to '" << filename << "'.\n";
    }
}

static void doLoadFromFile(GuestListManager& manager) {
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

// ============================================================================
// Main
// ============================================================================

int main() {
    GuestListManager manager;
    int choice;

    std::cout << "  Welcome to the Wedding Guest List Manager.\n";

    while (true) {
        displayMenu();
        std::cout << "  Enter choice (1-8): ";
        if (!(std::cin >> choice)) {
            clearInputStream();
            std::cout << "  Invalid input. Please enter a number.\n";
            continue;
        }
        clearInputStream();

        switch (choice) {
            case 1:
                doAddGuest(manager);
                break;
            case 2:
                doRemoveGuest(manager);
                break;
            case 3:
                doUpdateRsvp(manager);
                break;
            case 4:
                manager.displayAllGuests();
                break;
            case 5:
                doDisplayTotal(manager);
                break;
            case 6:
                doSaveToFile(manager);
                break;
            case 7:
                doLoadFromFile(manager);
                break;
            case 8:
                std::cout << "  Goodbye!\n";
                return 0;
            default:
                std::cout << "  Invalid choice. Please enter 1-8.\n";
        }
    }
}
