#include <iostream>
#include "ReservationManager.h"

using namespace std;

int main()
{
    ReservationManager manager;

    manager.loadResources("Resources.txt");
    manager.loadReservations("Reservations.txt");

    int choice;

    do
        {
        cout << endl;
        cout << "       COMPUS RESOURCE RESERVATION SYSTEM      " << endl;
        cout << endl;
        cout << "1. Display All Resources" << endl;
        cout << "2. Display Resource Availability" << endl;
        cout << "3. Create Reservation" << endl;
        cout << "4. Cancel Reservation" << endl;
        cout << "5. Display Active Reservations" << endl;
        cout << "6. Add Student to Waiting List" << endl;
        cout << "7. Display Waiting List" << endl;
        cout << "8. Undo Last Cancellation" << endl;
        cout << "9. Display Cancellation History" << endl;
        cout << "10. Exit" << endl;

        cout << "Enter: ";
        cin >> choice;

        switch (choice)
            {
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
                manager.addToWaitingList();
                break;
            case 7:
                manager.displayWaitingList();
                break;
            case 8:
                manager.undoCancellation();
                break;
            case 9:
                manager.displayCancellationHistory();
                break;
            case 10:
                cout << "Goodbye!!!!!" << endl;
                break;
            default:
                cout << "Invalid. Try again." << endl;
        }

    } while (choice != 10);

    return 0;
}