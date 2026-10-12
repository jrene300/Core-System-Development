#include "Tests.h"
#include "ReservationManager.h"
#include "Sorting.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>

using namespace std;

static int passed = 0;
static int failed = 0;

static void check(bool condition, const string& name)
{
    if (condition) { passed++; cout << "  [PASS] " << name << endl; }
    else           { failed++; cout << "  [FAIL] " << name << endl; }
}

class Silence
{
    ostringstream sink;
    streambuf* old;
public:
    Silence() : old(cout.rdbuf(sink.rdbuf())) {}
    ~Silence() { cout.rdbuf(old); }
};

class FeedInput
{
    istringstream in;
    streambuf* old;
public:
    FeedInput(const string& text) : in(text), old(cin.rdbuf(in.rdbuf())) {}
    ~FeedInput() { cin.rdbuf(old); cin.clear(); }
};

static void writeFile(const string& name, const string& text)
{
    ofstream f(name);
    f << text;
}

static const char* RES_FILE  = "_test_resources.txt";
static const char* RESV_FILE = "_test_reservations.txt";
static void fill(ReservationManager& m)
{
    writeFile(RES_FILE,
        "R101|Study Room 101|Study Room|Available\n"
        "R102|Laptop 01|Laptop|Available\n"
        "R103|3D Printer|Lab Equipment|Unavailable\n"
        "R104|Arduino Kit|Lab Equipment|Available\n"
        "R101|Duplicate Room|Study Room|Available\n"
        "BADLINE\n");
    writeFile(RESV_FILE,
        "1|1001|Alice|R101|12/31/2026\n"
        "2|1002|Bob|R101|01/05/2027\n"
        "3|1001|Alice|R102|03/01/2026\n"
        "4|1003|Cara|R104|11/15/2026\n"
        "1|1009|Dup|R102|05/05/2026\n"
        "x|y|Bad|R102|05/05/2026\n");
    Silence s;
    m.loadResources(RES_FILE);
    m.loadReservations(RESV_FILE);
    remove(RES_FILE);
    remove(RESV_FILE);
}

static void testMergeSort()
{
    cout << "Merge Sort (template):" << endl;
    auto asc = [](int a, int b) { return a < b; };

    vector<int> v = {5, 2, 9, 1, 5, 6, -3};
    mergeSortBy(v, asc);
    check(v == vector<int>({-3, 1, 2, 5, 5, 6, 9}), "sorts unsorted ints with duplicates");

    vector<int> empty;
    mergeSortBy(empty, asc);
    check(empty.empty(), "empty vector");

    vector<int> one = {7};
    mergeSortBy(one, asc);
    check(one == vector<int>({7}), "single element");

    vector<int> rev = {4, 3, 2, 1};
    mergeSortBy(rev, asc);
    check(rev == vector<int>({1, 2, 3, 4}), "reverse-ordered input");

    vector<int> desc = {1, 3, 2};
    mergeSortBy(desc, [](int a, int b) { return a > b; });
    check(desc == vector<int>({3, 2, 1}), "descending comparator");
}

bool runSelfTests()
{
    passed = 0;
    failed = 0;
    cout << endl << "========== SELF-TESTS ==========" << endl;

    testMergeSort();

    cout << "File loading:" << endl;
    {
        ReservationManager m;
        fill(m);
        check(m.getResourceCount() == 4, "4 resources loaded (duplicate and bad line skipped)");
        check(m.getReservationCount() == 4, "4 reservations loaded (duplicate and bad line skipped)");

        ReservationManager empty;
        {
            Silence s;
            empty.loadResources("no_such_file.txt");
            empty.loadReservations("no_such_file.txt");
        }
        check(empty.getResourceCount() == 0 && empty.getReservationCount() == 0,
              "missing files handled without crashing");
    }

    cout << "Linear Search:" << endl;
    {
        ReservationManager m;
        fill(m);
        check(m.findResource("R102") == 1, "finds resource at index 1");
        check(m.findResource("R104") == 3, "finds last resource");
        check(m.findResource("R999") == -1, "missing resource returns -1");

        const Reservation* r = m.findReservation(3);
        check(r != nullptr && r->getStudentName() == "Alice", "finds reservation by ID");
        check(m.findReservation(99) == nullptr, "missing reservation returns null");

        check(m.findReservationsByStudent(1001).size() == 2, "student with 2 reservations");
        check(m.findReservationsByStudent(1003).size() == 1, "student with 1 reservation");
        check(m.findReservationsByStudent(9999).empty(), "unknown student returns none");
    }

    cout << "Sorting:" << endl;
    {
        ReservationManager m;
        fill(m);

        vector<Resource> byName = m.getSortedResources(1);
        check(byName[0].getResourceID() == "R103" && byName[1].getResourceID() == "R104" &&
              byName[2].getResourceID() == "R102" && byName[3].getResourceID() == "R101",
              "resources sorted by name");

        vector<Resource> byType = m.getSortedResources(2);
        check(byType[0].getResourceID() == "R103" && byType[1].getResourceID() == "R104" &&
              byType[2].getResourceID() == "R102" && byType[3].getResourceID() == "R101",
              "resources sorted by type");

        vector<Resource> byPop = m.getSortedResources(3);
        check(byPop[0].getResourceID() == "R101" && byPop[3].getResourceID() == "R103",
              "resources sorted by popularity (most reserved first)");

        vector<Reservation> byDate = m.getReservationsSortedByDate();
        check(byDate.size() == 4, "no reservations lost while sorting");
        check(byDate[0].getReservationID() == 3 && byDate[1].getReservationID() == 4 &&
              byDate[2].getReservationID() == 1 && byDate[3].getReservationID() == 2,
              "reservations in chronological order (across years)");

        check(m.findResource("R101") == 0, "original resource order unchanged");
    }

    cout << "Reservation validation:" << endl;
    {
        ReservationManager m;
        fill(m);
        bool dupID, unavail, noResource, doubleBook, badStudent, badDate, badDate2, good;
        {
            Silence s;
            dupID      = m.validateReservation(1, 1005, "R102", "05/05/2026");
            unavail    = m.validateReservation(11, 1005, "R103", "05/05/2026");
            noResource = m.validateReservation(12, 1005, "R999", "05/05/2026");
            doubleBook = m.validateReservation(13, 1005, "R101", "12/31/2026");
            badStudent = m.validateReservation(14, 0, "R102", "05/05/2026");
            badDate    = m.validateReservation(15, 1005, "R102", "99/99/2026");
            badDate2   = m.validateReservation(17, 1005, "R102", "02/29/2026");
            good       = m.validateReservation(16, 1005, "R102", "05/05/2026");
        }
        check(!dupID, "duplicate reservation ID rejected");
        check(!unavail, "unavailable resource rejected");
        check(!noResource, "unknown resource rejected");
        check(!doubleBook, "same resource + same date rejected");
        check(!badStudent, "invalid student ID rejected");
        check(!badDate && !badDate2, "invalid / impossible dates rejected");
        check(good, "valid reservation accepted");
    }

    cout << "Create / Cancel / Undo:" << endl;
    {
        ReservationManager m;
        fill(m);
        int afterCreate, afterCancel, histAfterCancel, afterBadCancel, afterUndo, afterUndo2;
        {
            Silence s;
            {
                FeedInput in("50\n1009\nEve Adams\nR102\n05/05/2026\n");
                m.createReservation();
            }
            afterCreate = m.getReservationCount();
            {
                FeedInput in("2\n");
                m.cancelReservation();
            }
            afterCancel = m.getReservationCount();
            histAfterCancel = m.getHistorySize();
            {
                FeedInput in("999\n");
                m.cancelReservation();
            }
            afterBadCancel = m.getReservationCount();
            m.undoCancellation();
            afterUndo = m.getReservationCount();
            m.undoCancellation();   // nothing left to undo
            afterUndo2 = m.getReservationCount();
        }
        check(afterCreate == 5 && m.findReservation(50) != nullptr, "create adds a reservation");
        check(afterCancel == 4 && histAfterCancel == 1, "cancel removes it and pushes to history");
        check(afterBadCancel == 4, "cancelling unknown ID changes nothing");
        check(afterUndo == 5 && m.findReservation(2) != nullptr, "undo restores last cancellation");
        check(afterUndo2 == 5, "undo on empty history changes nothing");
    }

    cout << "Undo conflict:" << endl;
    {
        ReservationManager m;
        fill(m);
        int before, after;
        {
            Silence s;
            { FeedInput in("1\n"); m.cancelReservation(); }
            { FeedInput in("50\n1009\nEve\nR101\n12/31/2026\n"); m.createReservation(); }
            before = m.getReservationCount();
            m.undoCancellation();
            after = m.getReservationCount();
        }
        check(before == after && m.findReservation(1) == nullptr, "undo refused when slot was re-booked");
        check(m.getHistorySize() == 1, "refused undo keeps the entry in history");
    }

    cout << "Waiting list:" << endl;
    {
        ReservationManager m;
        fill(m);
        bool a, b, c, bad;
        {
            Silence s;
            a = m.addWaitingStudent("Zed", "R101");
            b = m.addWaitingStudent("Amy", "R101");
            c = m.addWaitingStudent("Bo", "R102");
            bad = m.addWaitingStudent("Nope", "R999");
        }
        check(a && b && c, "students added to waiting list");
        check(!bad, "unknown resource rejected");
        check(m.getWaitingCount("R101") == 2 && m.getWaitingCount("R102") == 1, "per-resource counts");
        check(m.getWaitingCount("R104") == 0, "resource with nobody waiting has count 0");
        check(m.getTotalWaiting() == 3, "total waiting count");
        {
            Silence s;
            FeedInput in("1\n");
            m.cancelReservation();
        }
        check(m.getWaitingCount("R101") == 1 && m.getTotalWaiting() == 2, "cancel notifies and removes first waiter (FIFO)");
        check(m.getWaitingCount("R102") == 1, "other resource's queue untouched");
    }

    cout << "Reports:" << endl;
    {
        ReservationManager m;
        fill(m);
        vector<ResourceUsage> usage = m.getResourceUsage();
        int sum = 0;
        for (const ResourceUsage& u : usage) sum += u.reservationCount;
        check(usage.size() == 4 && sum == m.getReservationCount(), "utilization counts match reservations");

        vector<ResourceUsage> top = m.getMostRequested();
        check(top[0].resourceID == "R101" && top[0].reservationCount == 2, "most requested resource first");
        bool ordered = true;
        for (size_t i = 1; i < top.size(); i++)
            if (top[i - 1].reservationCount < top[i].reservationCount) ordered = false;
        check(ordered, "most-requested list is in descending order");
    }

    cout << endl << "Results: " << passed << " passed, " << failed << " failed" << endl;
    return failed == 0;
}
