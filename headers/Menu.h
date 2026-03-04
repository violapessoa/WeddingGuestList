/*
 * Menu.h
 * Menu and UI handler declarations for the Wedding Guest List Manager.
 */

#ifndef WEDDING_GUEST_LIST_MENU_H
#define WEDDING_GUEST_LIST_MENU_H

class GuestListManager;

void displayMenu();
void doAddGuest(GuestListManager& manager);
void doRemoveGuest(GuestListManager& manager);
void doUpdateRsvp(GuestListManager& manager);
void doDisplayTotal(GuestListManager& manager);
void doSaveToFile(GuestListManager& manager);
void doLoadFromFile(GuestListManager& manager);

#endif /* WEDDING_GUEST_LIST_MENU_H */
