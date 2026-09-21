#include <iostream>
#include "ReservationManager.h"

using namespace std;

int main() {

    // Creates the manager that controls our resources
    // and reservations.
    ReservationManager manager;

    // Loads the resource information from the data file.
    manager.loadResources("../data/resources.txt");

    // Loads the reservation information from the data file.
    manager.loadReservations("../data/reservations.txt");

    int choice;

    // Keeps showing the menu until the user chooses 6.
    do {

        cout << endl;
        cout << "===== CAMPUS RESOURCE RESERVATION SYSTEM ====="
             << endl;

        cout << "1. Display All Resources" << endl;
        cout << "2. Display Resource Availability" << endl;
        cout << "3. Create Reservation" << endl;
        cout << "4. Cancel Reservation" << endl;
        cout << "5. Display Active Reservations" << endl;
        cout << "6. Exit" << endl;

        cout << "Enter choice: ";
        cin >> choice;

        // Determines which menu option the user selected.
        switch (choice) {

            case 1:
                manager.displayResources();
                break;

            case 2:
                manager.displayAvailability();
                break;

            case 3:
                manager.createReservation();
                break;

            case 4:
                manager.cancelReservation();
                break;

            case 5:
                manager.displayReservations();
                break;

            case 6:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Invalid choice. Please try again."
                     << endl;
        }

    } while (choice != 6);

    return 0;
}