/*
 * Guest.h
 * Declaration of the Guest class for the Wedding Guest List Manager.
 */

#ifndef WEDDING_GUEST_LIST_GUEST_H
#define WEDDING_GUEST_LIST_GUEST_H

#include <string>

class Guest {
private:
    std::string firstName;
    std::string lastName;
    bool rsvpStatus;
    int numberOfGuests;

public:
    Guest();
    Guest(const std::string& first, const std::string& last,
          bool rsvp = false, int numGuests = 1);

    std::string getFirstName() const;
    std::string getLastName() const;
    bool getRsvpStatus() const;
    int getNumberOfGuests() const;

    void setFirstName(const std::string& first);
    void setLastName(const std::string& last);
    void setRsvpStatus(bool status);
    void setNumberOfGuests(int num);
};

#endif /* WEDDING_GUEST_LIST_GUEST_H */
