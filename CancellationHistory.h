#ifndef CANCELLATION_HISTORY_H
#define CANCELLATION_HISTORY_H

#include "Reservation.h"

class CancellationHistory {

private:

    struct Node {

        Reservation data;

        Node* next;

        explicit Node(const Reservation& r) : data(r), next(nullptr) {}

    };



    Node* top;

    int size;

public:

    CancellationHistory();

    ~CancellationHistory();


    // Push a newly-cancelled reservation onto the history stack.

    void push(const Reservation& r);



    // Pop the most recently cancelled reservation (for Undo).

    // Returns false if the stack is empty.

    bool pop(Reservation& outReservation);

    // Look at the most recent cancellation without removing it.

    bool peek(Reservation& outReservation) const;


    void display() const;

    bool isEmpty() const;

    int getSize() const;

};

#endif // CANCELLATION_HISTORY_H
