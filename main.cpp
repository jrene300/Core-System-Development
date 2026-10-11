#include <iostream>
#include <limits>                //numeric_limits
#include "ReservationManager.h" // class

using namespace std;

int main()
{
    ReservationManager manager;    // create the manager object

    manager.loadResources("Resources.txt");        // loads resource from file 
    manager.loadReservations("Reservations.txt");  // load exisiting reservations from file

    int choice;            //int user's menu selection

    do                       // keeps showing menu until user picks Exit
        {
        cout << endl;
        cout << "       CAMPUS RESOURCE RESERVATION SYSTEM      " << endl;
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
        cout << "10. Search Resource by ID" << endl;        
        cout << "11. Search Reservation by ID" << endl;
        cout << "12. Search Reservations by Student ID" << endl;
        cout << "13. Sort Resources" << endl;
        cout << "14. Exit" << endl;

        cout << "Enter: ";
        if (!(cin >> choice))        //true if user does not type a number 
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes bad inputline
            choice = 0;                                          // 0 matches no case "invalid"
        }

        switch (choice)        // runs the function that matches the menu number
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
            case 10:    // linear search: Resource by ID
                manager.searchResource();
                break;
            case 11:    // linear search: Reservation by ID
                manager.searchReservationByID();
                break;
            case 12:    // linear search: all student's reservations
                manager.searchReservationsByStudent();
                break;
            case 13:    // merge sort 
                manager.sortResources();
                break;
            case 14:
                cout << "Goodbye!!!!!" << endl;
                break;
            default:    // any other 
                cout << "Invalid. Try again." << endl;    
        }

    } while (choice != 14);    // loop again unless user picks exit

    return 0;                   // program ends
}
