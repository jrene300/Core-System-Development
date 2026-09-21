#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


// Loads all resources from the resources.txt file.
void ReservationManager::loadResources(string filename) {

    // Opens the file for reading.
    ifstream file(filename);

    // Checks if the file could not be opened.
    if (!file) {
        cout << "Error: Could not open resource file." << endl;
        return;
    }

    string line;

    // Reads the file one line at a time.
    while (getline(file, line)) {

        string id;
        string name;
        string type;
        string status;

        // Allows us to split the line using the | symbol.
        stringstream ss(line);

        // Reads each piece of information from the line.
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status);

        // Creates a Resource object.
        Resource resource(id, name, type, status);

        // Adds the Resource object to the resources vector.
        resources.push_back(resource);
    }

    // Closes the file.
    file.close();
}


// Loads all reservations from the reservations.txt file.
void ReservationManager::loadReservations(string filename) {

    // Opens the file for reading.
    ifstream file(filename);

    // Checks if the file could not be opened.
    if (!file) {
        cout << "Error: Could not open reservation file." << endl;
        return;
    }

    string line;

    // Reads the file one line at a time.
    while (getline(file, line)) {

        string reservationID;
        string studentID;
        string studentName;
        string resourceID;
        string reservationDate;

        // Splits the line using the | symbol.
        stringstream ss(line);

        // Reads each piece of reservation information.
        getline(ss, reservationID, '|');
        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceID, '|');
        getline(ss, reservationDate);

        // Converts the ID strings into integers.
        int rID = stoi(reservationID);
        int sID = stoi(studentID);

        // Creates a Reservation object.
        Reservation reservation(
            rID,
            sID,
            studentName,
            resourceID,
            reservationDate
        );

        // Adds the reservation to the linked list.
        reservations.push_back(reservation);
    }

    // Closes the file.
    file.close();
}


// Displays every resource.
void ReservationManager::displayResources() const {

    cout << endl;
    cout << "===== ALL RESOURCES =====" << endl;

    // Goes through every Resource in the vector.
    for (const Resource& resource : resources) {
        resource.display();
    }
}


// Displays the availability of every resource.
void ReservationManager::displayAvailability() const {

    cout << endl;
    cout << "===== RESOURCE AVAILABILITY =====" << endl;

    // Goes through every Resource in the vector.
    for (const Resource& resource : resources) {

        cout << resource.getResourceID()
             << ": "
             << resource.getAvailability()
             << endl;
    }
}


// Checks whether a resource ID exists.
bool ReservationManager::resourceExists(string resourceID) const {

    // Searches through every resource.
    for (const Resource& resource : resources) {

        // Checks if the IDs match.
        if (resource.getResourceID() == resourceID) {
            return true;
        }
    }

    // Resource was not found.
    return false;
}


// Checks whether a reservation ID already exists.
bool ReservationManager::reservationIDExists(int reservationID) const {

    // Searches through every reservation.
    for (const Reservation& reservation : reservations) {

        // Checks if the IDs match.
        if (reservation.getReservationID() == reservationID) {
            return true;
        }
    }

    // Reservation ID was not found.
    return false;
}


// Checks whether a resource is already reserved on a specific date.
bool ReservationManager::resourceReservedOnDate(
    string resourceID,
    string date) const {

    // Searches through every reservation.
    for (const Reservation& reservation : reservations) {

        // Checks both the resource ID and date.
        if (reservation.getResourceID() == resourceID &&
            reservation.getReservationDate() == date) {

            return true;
        }
    }

    // No reservation was found for that resource on that date.
    return false;
}


// Validates information before creating a reservation.
bool ReservationManager::validateReservation(
    int reservationID,
    int studentID,
    string resourceID,
    string reservationDate) const {

    // Checks for a duplicate reservation ID.
    if (reservationIDExists(reservationID)) {

        cout << "Error: Reservation ID already exists."
             << endl;

        return false;
    }

    // Checks that the student ID is positive.
    if (studentID <= 0) {

        cout << "Error: Invalid student ID."
             << endl;

        return false;
    }

    // Checks that the resource exists.
    if (!resourceExists(resourceID)) {

        cout << "Error: Resource does not exist."
             << endl;

        return false;
    }

    // Checks whether the resource is currently unavailable.
    for (const Resource& resource : resources) {

        if (resource.getResourceID() == resourceID &&
            resource.getAvailability() == "Unavailable") {

            cout << "Error: Resource is currently unavailable."
                 << endl;

            return false;
        }
    }

    // Checks whether the resource is already reserved
    // on the requested date.
    if (resourceReservedOnDate(resourceID, reservationDate)) {

        cout << "Error: Resource is already reserved on that date."
             << endl;

        return false;
    }

    // All validation checks passed.
    return true;
}


// Creates a new reservation.
void ReservationManager::createReservation() {

    int reservationID;
    int studentID;

    string studentName;
    string resourceID;
    string reservationDate;

    cout << endl;
    cout << "===== CREATE RESERVATION =====" << endl;

    cout << "Enter Reservation ID: ";
    cin >> reservationID;

    cout << "Enter Student ID: ";
    cin >> studentID;

    // Removes the leftover newline from the input.
    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    cout << "Enter Resource ID: ";
    cin >> resourceID;

    cout << "Enter Reservation Date: ";
    cin >> reservationDate;

    // Validates the reservation before creating it.
    if (!validateReservation(
            reservationID,
            studentID,
            resourceID,
            reservationDate)) {

        cout << "Reservation was not created."
             << endl;

        return;
    }

    // Creates the new Reservation object.
    Reservation reservation(
        reservationID,
        studentID,
        studentName,
        resourceID,
        reservationDate
    );

    // Adds the reservation to the linked list.
    reservations.push_back(reservation);

    cout << "Reservation created successfully!"
         << endl;
}


// Cancels an existing reservation.
void ReservationManager::cancelReservation() {

    int reservationID;

    cout << endl;
    cout << "===== CANCEL RESERVATION =====" << endl;

    cout << "Enter Reservation ID: ";
    cin >> reservationID;

    // Searches through the linked list.
    for (auto it = reservations.begin();
         it != reservations.end();
         ++it) {

        // Checks if the reservation ID matches.
        if (it->getReservationID() == reservationID) {

            // Removes the reservation from the linked list.
            reservations.erase(it);

            cout << "Reservation cancelled successfully!"
                 << endl;

            return;
        }
    }

    // Reservation was not found.
    cout << "Error: Reservation not found."
         << endl;
}


// Displays all active reservations.
void ReservationManager::displayReservations() const {

    cout << endl;
    cout << "===== ACTIVE RESERVATIONS ====="
         << endl;

    // Checks whether there are no reservations.
    if (reservations.empty()) {

        cout << "No active reservations."
             << endl;

        return;
    }

    // Displays every active reservation.
    for (const Reservation& reservation : reservations) {
        reservation.display();
    }
}