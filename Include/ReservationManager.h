#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <vector>
#include <string>

#include "Resource.h"
#include "Reservation.h"

using namespace std;

class ReservationManager {
private:
    vector<Resource> resources;
    vector<Reservation> reservations;

public:
    void loadResources(string filename);
    void loadReservations(string filename);

    void displayResources() const;
    void displayAvailability() const;

    void createReservation();
    void cancelReservation();
    void displayReservations() const;

    bool validateReservation(int reservationID,
                             int studentID,
                             string resourceID,
                             string reservationDate) const;

    bool resourceExists(string resourceID) const;
    bool reservationIDExists(int reservationID) const;

    bool resourceReservedOnDate(string resourceID,
                                string date) const;
};

#endif