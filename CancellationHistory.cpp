#include "CancellationHistory.h"
#include <iostream>

using namespace std;

CancellationHistory::CancellationHistory() : top(nullptr), size(0) {}

CancellationHistory::~CancellationHistory()
{

    Node* current = top;

    while (current != nullptr)
        {

        Node* toDelete = current;

        current = current->next;

        delete toDelete;

    }

    top = nullptr;

}

void CancellationHistory::push(const Reservation& r)
{

    Node* newNode = new Node(r);

    newNode->next = top;

    top = newNode;

    size++;

}

bool CancellationHistory::pop(Reservation& outReservation)
{

    if (top == nullptr)
        {

        return false;

    }

    Node* toRemove = top;

    outReservation = toRemove->data;

    top = top->next;

    delete toRemove;

    size--;

    return true;

}



bool CancellationHistory::peek(Reservation& outReservation) const
{

    if (top == nullptr)
        {

        return false;

    }

    outReservation = top->data;

    return true;

}
void CancellationHistory::display()
const
{

    if (top == nullptr)
        {
        cout << "  (no cancellation history)" << endl;

        return;
    }

    Node* current = top;

    int position = 1;

    while (current != nullptr)
        {

        std::cout << "  " << position << ". ";

        current->data.display();

        current = current->next;

        position++;
    }
}
bool CancellationHistory::isEmpty()
const
{
    return top == nullptr;
}

int CancellationHistory::getSize()
const
{

    return size;

}
