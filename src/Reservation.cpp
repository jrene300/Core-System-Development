#include "Reservation.h"
#include <iostream>

using namespace std;

Reservation::Reservation(int reservationID,
                         int studentID,
                         string studentName,
                         string resourceID,
                         string reservationDate) {

    this->reservationID = reservationID;
    this->studentID = studentID;
    this->studentName = studentName;
    this->resourceID = resourceID;
    this->reservationDate = reservationDate;
}

int Reservation::getReservationID() const {
    return reservationID;
}

int Reservation::getStudentID() const {
    return studentID;
}

string Reservation::getStudentName() const {
    return studentName;
}

string Reservation::getResourceID() const {
    return resourceID;
}

string Reservation::getReservationDate() const {
    return reservationDate;
}

void Reservation::display() const {
    cout << reservationID << " | "
         << studentID << " | "
         << studentName << " | "
         << resourceID << " | "
         << reservationDate << endl;
}