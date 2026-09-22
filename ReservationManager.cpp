#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

void ReservationManager::loadResources(string filename)
{
    ifstream file(filename);
    if (!file)
        {
        cout << "Could not open resource file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
        {
        string id, name, type, status;
        stringstream ss(line);
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, type, '|');
        getline(ss, status);

        Resource resource(id, name, type, status);
        resources.push_back(resource);
    }
    file.close();
}


void ReservationManager::loadReservations(string filename)
{
    ifstream file(filename);
    if (!file)
        {
        cout << "Could not open reservation file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
        {
        string reservationID, studentID, studentName, resourceID, reservationDate;
        stringstream ss(line);
        getline(ss, reservationID, '|');
        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceID, '|');
        getline(ss, reservationDate);

        int rID = stoi(reservationID);
        int sID = stoi(studentID);

        Reservation reservation(rID, sID, studentName, resourceID, reservationDate);
        reservations.push_back(reservation);
    }
    file.close();
}

void ReservationManager::displayResources() const
{
    cout << endl << "    ALL RESOURCES    " << endl;
    for (const Resource& resource : resources)
        {
        resource.display();
    }
}


void ReservationManager::displayAvailability() const
{
    cout << endl << "   RESOURCE AVAILABLE   " << endl;
    for (const Resource& resource : resources)
        {
        cout << resource.getResourceID() << ": " << resource.getAvailability() << endl;
    }
}


bool ReservationManager::resourceExists(string resourceID) const
{
    for (const Resource& resource : resources)
        {
        if (resource.getResourceID() == resourceID)
            {
            return true;
        }
    }
    return false;
}


bool ReservationManager::reservationIDExists(int reservationID) const
{
    for (const Reservation& reservation : reservations)
        {
        if (reservation.getReservationID() == reservationID)
            {
            return true;
        }
    }
    return false;
}


bool ReservationManager::resourceReservedOnDate(string resourceID, string date) const
{
    for (const Reservation& reservation : reservations)
        {
        if (reservation.getResourceID() == resourceID &&
            reservation.getReservationDate() == date)
            {
            return true;
        }
    }
    return false;
}


bool ReservationManager::validateReservation(
    int reservationID,
    int studentID,
    string resourceID,
    string reservationDate) const
{

    if (reservationIDExists(reservationID))
        {
        cout << "Reservation ID already exists." << endl;
        return false;
    }

    if (studentID <= 0)
        {
        cout << "Invalid student ID." << endl;
        return false;
    }

    if (!resourceExists(resourceID))
        {
        cout << "Resource does not exist." << endl;
        return false;
    }

    for (const Resource& resource : resources)
        {
        if (resource.getResourceID() == resourceID &&
            resource.getAvailability() == "Unavailable")
            {
            cout << "Resource is currently not available." << endl;
            return false;
        }
    }

    if (resourceReservedOnDate(resourceID, reservationDate))
        {
        cout << "Resource is already reserved on that date." << endl;
        return false;
    }

    return true;
}


void ReservationManager::createReservation()
{
    int reservationID, studentID;
    string studentName, resourceID, reservationDate;

    cout << endl << "    CREATE RESERVATION   " << endl;

    cout << "Reservation ID: ";
    cin >> reservationID;

    cout << "Enter Student ID: ";
    cin >> studentID;

    cin.ignore();

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    cout << "Resource ID: ";
    cin >> resourceID;

    cout << "Reservation Date: ";
    cin >> reservationDate;

    if (!validateReservation(reservationID, studentID, resourceID, reservationDate))
        {
        cout << "Reservation was not created." << endl;
        return;
    }

    Reservation reservation(reservationID, studentID, studentName, resourceID, reservationDate);
    reservations.push_back(reservation);

    cout << "Reservation created!!!!" << endl;
}


void ReservationManager::cancelReservation()
{
    int reservationID;

    cout << endl << "   CANCEL RESERVATION    " << endl;
    cout << "Reservation ID: ";
    cin >> reservationID;

    for (auto it = reservations.begin(); it != reservations.end(); ++it)
        {
        if (it->getReservationID() == reservationID)
            {
            history.push(*it);
            reservations.erase(it);
            cout << "Reservation cancelled!!!!" << endl;
            return;
        }
    }

    cout << " Reservation not found." << endl;
}

void ReservationManager::displayReservations() const
{
    cout << endl << "    ACTIVE RESERVATIONS     " << endl;

    if (reservations.empty())
        {
        cout << "No active reservations." << endl;
        return;
    }

    for (const Reservation& reservation : reservations)
        {
        reservation.display();
    }
}


void ReservationManager::addToWaitingList()
{
    string name;

    cout << endl << "    ADD TO WAITING LIST   " << endl;
    cout << "Student Name: ";
    cin.ignore();
    getline(cin, name);

    waitingQueue.addStudent(name);
    cout << "Added to waiting list." << endl;
}


void ReservationManager::displayWaitingList() const
{
    cout << endl << "    WAITING LIST   " << endl;
    waitingQueue.displayWaitingList();
}


void ReservationManager::undoCancellation()
{
    Reservation restored(0, 0, "", "", "");

    if (history.pop(restored))
        {
        reservations.push_back(restored);
        cout << "Restored reservation:" << endl;
        restored.display();
    }
    else
        {
        cout << "No cancellations to undo." << endl;
    }
}


void ReservationManager::displayCancellationHistory() const
{
    cout << endl << "    CANCELLATION HISTORY    " << endl;
    history.display();
}