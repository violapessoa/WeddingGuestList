/*
 * main.cpp
 * Entry point for the Wedding Guest List Manager.
 */

#include "GuestListManager.h"
#include "Menu.h"
#include "Utils.h"
#include <iostream>

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
