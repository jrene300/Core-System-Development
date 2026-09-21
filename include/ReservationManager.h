#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <vector>
#include <string>
#include <list>
#include "Resource.h"
#include "Reservation.h"

using namespace std;

class ReservationManager {
private:

    // Stores campus resources.
    vector<Resource> resources;

    // all active reservations.
    list<Reservation> reservations;

public:

    // Loads resource information from a file.
    void loadResources(string filename);
    void loadReservations(string filename);
    void displayResources() const;
    void displayAvailability() const;
    void createReservation();
    void cancelReservation();
    void displayReservations() const;

    // Checks if reservation request is valid.
    bool validateReservation(int reservationID,
                             int studentID,
                             string resourceID,
                             string reservationDate) const;
    // resource ID exists.
    bool resourceExists(string resourceID) const;
    // reservation ID already exists.
    bool reservationIDExists(int reservationID) const;
    //  date resource is already reserved
    bool resourceReservedOnDate(string resourceID,
                                string date) const;
};

#endif