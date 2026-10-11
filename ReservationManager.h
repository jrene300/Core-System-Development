#ifndef RESERVATION_MANAGER_H   // prevents the header from being incuded twice
#define RESERVATION_MANAGER_H

#include <vector>                //for resource inventory
#include <string>                //for stirng
#include <list>                  //for list (linked lists of active reservations)
#include "Resource.h"            //resource class
#include "Reservation.h"         // reservation class
#include "WaitingQueue.h"        // FIFO waitng list
#include "CancellationHistory.h"    //undo history

using namespace std;
//includes all resources, active reservations, waiting queue, cancellation
class ReservationManager
{
private:
    vector<Resource> resources;
    list<Reservation> reservations;
    WaitingQueue waitingQueue;
    CancellationHistory history;
//linear search
int linearSearchResource(const string& id) const; //returns index in vector or -1 if not found
const Reservation* linearSearchReservation(int id) const; // returns pointer to match, or nullptr if not found

//merge sort
int countReservationsFor(const string& resourceID) const; //number of active reservations
bool resourceComesBefore(const Resource& a, const Resource& b, int criteria) const; // comparison used by the sort
void mergeSort(vector<Resource>& v, int left, int right, int criteria) const;       // recursive spliting step
void mergeHalves(vector<Resource>& v, int left, int mid, int right, int criteria) const; //merges


public:
    void loadResources(string filename);    // reads resources from a text file
    void loadReservations(string filename);    // reads reservation from a text file
    void displayResources() const;            //prints every resource 
    void displayAvailability() const;        //prints each resource's availability
    void createReservation();                //asks user for info and adds a reservation
    void cancelReservation();                // removes a reservation and pushes it on the history stack
    void displayReservations() const;        //prints all active reservations 
//checks if all are true
    bool validateReservation(int reservationID,
                             int studentID,
                             string resourceID,
                             string reservationDate) const;
    bool resourceExists(string resourceID) const;
    bool reservationIDExists(int reservationID) const;
    bool resourceReservedOnDate(string resourceID,
                                string date) const;

    //searching 
    void searchResource() const;                // find a resource by ID
    void searchReservationByID() const;        // find a reservation based on ID
    void searchReservationsByStudent() const; // finds all reservation for one student

    //sorting 
    void sortResources()const;        //sort and display resources

    // Waiting list
    void addToWaitingList();
    void displayWaitingList() const;

    // Cancellation history
    void undoCancellation();
    void displayCancellationHistory() const;
};

#endif
