#include "ReservationManager.h"
#include <iostream>
#include <fstream>
#include <sstream>       // stringstream for splitting lines at '|'
#include <limits>        // numeric_limits, removes invalid input

using namespace std;

//reads int input from user and returns false if it is invalid
//prevents infinte loop crash from non-numeric input
static bool readInt(int& value)
{
    if (cin >> value) // input can only be a number
        return true;

    cin.clear();        // resets error
    cin.ignore(numeric_limits<streamsize>:: max(), '\n');     //discards invalid input
    return false;
}

//allows files to load correctly
static void stripCarriageReturn(string& line)
{
    if (!line.empty() && line[line.size() -1] == '\r')
        line.erase(line.size() -1);
}

//file loading
void ReservationManager::loadResources(string filename)
{
    ifstream file(filename);    // open file for reading
    if (!file)                   //if it could not be opened
        {
        cout << "Could not open resource file." << endl;   
        return;
    }

    string line;
    while (getline(file, line))        // reads one line at a time until the end of the file
        {
        stripCarriageReturn(line);
        if (line.empty())
            continue;
            
        string id, name, type, status;
        stringstream ss(line);    //splits thr line like a stream
        getline(ss, id, '|');    //text up to the first '|' to resource ID
        getline(ss, name, '|');    // next to resource name
        getline(ss, type, '|');    //next to resource type 
        getline(ss, status);        // availability

            //skips if there are any missing lines
            if (id.empty() || name.empty() || type.empty() || status.empty())
                continue;
            //skips duplicates of resource IDs, using linear search 
            if (linearSearchResource(id) != -1)
                continue;
            
        Resource resource(id, name, type, status);    //builds a resource object
        resources.push_back(resource);                //adds it to the end of the vector
    }
    file.close();
}


void ReservationManager::loadReservations(string filename)
{
    ifstream file(filename);            // opens reservation file
    if (!file)
        {
        cout << "Could not open reservation file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
        {
        stripCarriageReturn(line);
            if (line.empty())
                continue;
            
        string reservationID, studentID, studentName, resourceID, reservationDate;
        stringstream ss(line);
        getline(ss, reservationID, '|');
        getline(ss, studentID, '|');
        getline(ss, studentName, '|');
        getline(ss, resourceID, '|');
        getline(ss, reservationDate);

        int rID, sID;
        try
        {
            rID = stoi(reservationID);      // convert text to int (throws if not a number)
            sID = stoi(studentID);
        }
        catch (...)                         // catches any conversion error
        {
            continue;                       // skip the bad line instead of crashing
        }
 
        // Skip duplicate reservation IDs
        if (reservationIDExists(rID))
            continue;

        Reservation reservation(rID, sID, studentName, resourceID, reservationDate);
        reservations.push_back(reservation);
    }
    file.close();
}
// display 
void ReservationManager::displayResources() const
{
    cout << endl << "    ALL RESOURCES    " << endl;
    for (const Resource& resource : resources)    //loops over every resource by reference 
        {
        resource.display();        // print one resource
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
// searching 
int ReservationManager::linearSearchResource(const string& id) const
{
    for (size_t i = 0; i < resources.size(); i++)     // visit every position 0..size-1
    {
        if (resources[i].getResourceID() == id)       // does this resource's ID match?
            return (int)i;                            // yes: return where we found it
    }
    return -1;                                        // checked everything, no match
}
// checks reach reservation in the linked list
const Reservation* ReservationManager::linearSearchReservation(int id) const
{
    for (const Reservation& r : reservations)         // walk the linked list node by node
    {
        if (r.getReservationID() == id)               // does the ID match?
            return &r;                                // yes: return its address
    }
    return nullptr;                                   // not found
}

//if founf by linear search, a resource exists
bool ReservationManager::resourceExists(string resourceID) const
{
    return linearSearchResource(resourceID) != -1;
}
 
// A reservation ID is taken if the linear search returns a real pointer.
bool ReservationManager::reservationIDExists(int reservationID) const
{
    return linearSearchReservation(reservationID) != nullptr;
}

// returns true if reservation are already booked on this date
bool ReservationManager::resourceReservedOnDate(string resourceID, string date) const
{
    for (const Reservation& reservation : reservations)
    {
        if (reservation.getResourceID() == resourceID &&      // same resource AND
            reservation.getReservationDate() == date)         // same date
        {
            return true;                                      // conflict found
        }
    }
    return false;                                             // no conflict
}


////////////////////////////////////////////////////////////////////
//menu option: search for a resource by ID
void ReservationManager::searchResource() const
{
    string id;
    cout << endl << "    SEARCH RESOURCE    " << endl;
    cout << "Enter Resource ID: ";
    cin >> id;                                    // read the ID the user typed
 
    int index = linearSearchResource(id);         // run our linear search
    if (index == -1)
        cout << "Resource not found." << endl;
    else
        resources[index].display();               // use the index to print the match
}
 
// Menu option: search for a reservation by its ID.
void ReservationManager::searchReservationByID() const
{
    int id;
    cout << endl << "    SEARCH RESERVATION BY ID    " << endl;
    cout << "Enter Reservation ID: ";
    if (!readInt(id))                             // reject non-numeric input
    {
        cout << "Invalid input. Reservation ID must be a number." << endl;
        return;
    }
 
    const Reservation* r = linearSearchReservation(id);   // run our linear search
    if (r == nullptr)
        cout << "Reservation not found." << endl;
    else
        r->display();                             // print the match through the pointer
}
///////////////////////////////////////////////////////////////////////////////////////////
// Menu: List every reservation that belongs to one student
void ReservationManager::searchReservationsByStudent() const
{
    int studentID;
    cout << endl << "    SEARCH RESERVATIONS BY STUDENT    " << endl;
    cout << "Enter Student ID: ";
    if (!readInt(studentID))
    {
        cout << "Invalid input. Student ID must be a number." << endl;
        return;
    }
 
    bool found = false;                           // tracks whether we printed anything
    for (const Reservation& r : reservations)
    {
        if (r.getStudentID() == studentID)        // this reservation belongs to the student
        {
            r.display();
            found = true;
        }
    }
    if (!found)
        cout << "No reservations found for that student." << endl;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
// sorting active reservations a resource has
int ReservationManager::countReservationsFor(const string& resourceID) const
{
    int count = 0;
    for (const Reservation& r : reservations)
    {
        if (r.getResourceID() == resourceID)      // reservation is for this resource
            count++;
    }
    return count;
}
// ensure output goes through critera
bool ReservationManager::resourceComesBefore(const Resource& a, const Resource& b, int criteria) const
{
    if (criteria == 1)
        return a.getResourceName() < b.getResourceName();    // alphabetical by name
    if (criteria == 2)
        return a.getResourceType() < b.getResourceType();    // alphabetical by type
    // criteria 3: more reservations comes first (descending order)
    return countReservationsFor(a.getResourceID()) > countReservationsFor(b.getResourceID());
}
// Merge sort 
void ReservationManager::mergeSort(vector<Resource>& v, int left, int right, int criteria) const
{
    if (left >= right)
        return;                                  // base case: 0 or 1 element is already sorted
 
    int mid = left + (right - left) / 2;         // middle index (written this way to avoid overflow)
    mergeSort(v, left, mid, criteria);           // sort the left half
    mergeSort(v, mid + 1, right, criteria);      // sort the right half
    mergeHalves(v, left, mid, right, criteria);  // combine the two sorted halves
}
void ReservationManager::mergeHalves(vector<Resource>& v, int left, int mid, int right, int criteria) const
{
    vector<Resource> temp;                       // temporary storage for the merged result
    int i = left;                                // pointer into the left half
    int j = mid + 1;                             // pointer into the right half
 
    // Repeatedly take the smaller front element from either half
    while (i <= mid && j <= right)
    {
        // Take from the right half only if it is strictly earlier,
        // so equal items keep their original order (stable sort).
        if (resourceComesBefore(v[j], v[i], criteria))
        {
            temp.push_back(v[j]);                // right element goes first
            j++;
        }
        else
        {
            temp.push_back(v[i]);                // left element goes first
            i++;
        }
    }
    while (i <= mid)                             // copy any leftovers from the left half
    {
        temp.push_back(v[i]);
        i++;
    }
    while (j <= right)                           // copy any leftovers from the right half
    {
        temp.push_back(v[j]);
        j++;
    }
 
    for (size_t k = 0; k < temp.size(); k++)     // copy the merged result back into the original vector
        v[left + k] = temp[k];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
// menu: sort and display resources
void ReservationManager::sortResources() const
{
    int choice;
    cout << endl << "    SORT RESOURCES    " << endl;
    cout << "1. By Name" << endl;
    cout << "2. By Type" << endl;
    cout << "3. By Popularity (most reserved first)" << endl;
    cout << "Enter choice: ";
 
    if (!readInt(choice) || choice < 1 || choice > 3)   // must be a number from 1 to 3
    {
        cout << "Invalid sort option." << endl;
        return;
    }
 
    if (resources.empty())                       // nothing to sort
    {
        cout << "No resources to sort." << endl;
        return;
    }
 
    vector<Resource> sorted = resources;         // make a copy so the original order is untouched
    mergeSort(sorted, 0, (int)sorted.size() - 1, choice);   // sort the whole vector
 
    cout << endl << "    SORTED RESOURCES    " << endl;
    for (const Resource& r : sorted)
    {
        r.display();
        if (choice == 3)                         // for popularity, also show the count
        {
            cout << "     (active reservations: "
                 << countReservationsFor(r.getResourceID()) << ")" << endl;
        }
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
// checks every rule for new reservation, prints, and returns false on the first rule that fails
bool ReservationManager::validateReservation(
    int reservationID,
    int studentID,
    string resourceID,
    string reservationDate) const
{

    if (reservationID <= 0) // IDs must be positive
        {
        cout << "Invalid reservation ID." << endl;
        return false;
    }
 
    if (reservationIDExists(reservationID))      // no duplicate reservation IDs
    {
        cout << "Reservation ID already exists." << endl;
        return false;
    }
 
    if (studentID <= 0)                          // student IDs must be positive
    {
        cout << "Invalid student ID." << endl;
        return false;
    }
 
    int index = linearSearchResource(resourceID);   // find the resource (or -1)
    if (index == -1)
    {
        cout << "Resource does not exist." << endl;  // invalid resource ID
        return false;
    }
 
    if (resources[index].getAvailability() == "Unavailable")   // resource is out of service
    {
        cout << "Resource is currently not available." << endl;
        return false;
    }
 
    if (resourceReservedOnDate(resourceID, reservationDate))   // double-booking check
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
    if (!readInt(reservationID))                 // must be a number
    {
        cout << "Invalid input. Reservation ID must be a number." << endl;
        cout << "Reservation was not created." << endl;
        return;
    }
    cout << "Enter Student ID: ";
    if (!readInt(studentID))                     // must be a number
    {
        cout << "Invalid input. Student ID must be a number." << endl;
        cout << "Reservation was not created." << endl;
        return;
    }
 
    cin.ignore(numeric_limits<streamsize>::max(), '\n');   // discard leftover newline before getline
 
    cout << "Enter Student Name: ";
    getline(cin, studentName);                   // getline allows names with spaces
    if (studentName.empty())
    {
        cout << "Student name cannot be empty." << endl;
        cout << "Reservation was not created." << endl;
        return;
    }

    
    cout << "Resource ID: ";
    cin >> resourceID;

    cout << "Reservation Date: ";
    cin >> reservationDate;


    // run all validation rules before creating anything
    if (!validateReservation(reservationID, studentID, resourceID, reservationDate))
        {
        cout << "Reservation was not created." << endl;
        return;
    }

    Reservation reservation(reservationID, studentID, studentName, resourceID, reservationDate);
    reservations.push_back(reservation);        // adds to the end of a linked list

    cout << "Reservation created!!!!" << endl;
}


void ReservationManager::cancelReservation()
{
    int reservationID;

    cout << endl << "   CANCEL RESERVATION    " << endl;
    cout << "Reservation ID: ";
    if (!readInt(reservationID))
    {
        cout << "Invalid input. Reservation ID must be a number." << endl;
        return;
    }
    
// uses an iterator 
    for (auto it = reservations.begin(); it != reservations.end(); ++it)
        {
        if (it->getReservationID() == reservationID)
            {
            history.push(*it);        // saves a copy on the cancellation stack 
            reservations.erase(it);    // removes from the active list
            cout << "Reservation cancelled!!!!" << endl;
            return;            // stops the iterator
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

// waiting list
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

// cancellation history
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
