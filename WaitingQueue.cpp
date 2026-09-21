#include <iostream>
#include "WaitingQueue.h"
using namespace std;

WaitingQueue::WaitingQueue()
{
    front = nullptr;
    rear = nullptr;
    size = 0;
}

WaitingQueue::~WaitingQueue()
{
    WaitingStudent* current = front;
    while (current != nullptr)
        {
        WaitingStudent* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    front = nullptr;
    rear = nullptr;
}

void WaitingQueue::addStudent(const string& name)
{
    WaitingStudent* newNode = new WaitingStudent(name);

    if (rear == nullptr)
        {
        front = rear = newNode;
    }
    else
        {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}

void WaitingQueue::removeStudent()
{
    if (front == nullptr)
        {
        cout << "Waiting list is empty." << endl;
        return;
    }

    WaitingStudent* temp = front;
    front = front->next;

    if (front == nullptr)
        {
        rear = nullptr;
    }

    delete temp;
    size--;
}

void WaitingQueue::displayWaitingList() const
{
    if (front == nullptr)
        {
        cout << "Waiting list is empty." << endl;
        return;
    }

    WaitingStudent* current = front;
    int position = 1;
    while (current != nullptr)
        {
        cout << "  " << position << ". " << current->studentName << endl;
        current = current->next;
        position++;
    }
}

bool WaitingQueue::isEmpty() const
{
    return front == nullptr;
}

int WaitingQueue::getSize() const
{
    return size;
}
