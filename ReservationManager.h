#ifndef RESERVATION_MANAGER_H
#define RESERVATION_MANAGER_H

#include <vector>
#include <string>
#include <list>
#include "Resource.h"
#include "Reservation.h"
#include "WaitingQueue.h"
#include "CancellationHistory.h"

using namespace std;

class ReservationManager
{
private:
    vector<Resource> resources;
    list<Reservation> reservations;
    WaitingQueue waitingQueue;
    CancellationHistory history;

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

    // Waiting list
    void addToWaitingList();
    void displayWaitingList() const;

    // Cancellation history
    void undoCancellation();
    void displayCancellationHistory() const;
};

#endif
