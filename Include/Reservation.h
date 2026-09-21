#ifndef RESERVATION_H
#define RESERVATION_H
#include <string>

using namespace std;


class Reservation {

private:
    int reservationID;
    // Stores the reservation ID.
    int studentID;
    string studentName;
    string resourceID;
    string reservationDate;

public:
    Reservation(int reservationID,
                int studentID,
                string studentName,
                string resourceID,
                string reservationDate);
    // used to create a Reservation object.

    int getReservationID() const;
    // Returns the reservation ID.
    int getStudentID() const;
    string getStudentName() const;
    string getResourceID() const;
    string getReservationDate() const;
    void display() const;
};

#endif