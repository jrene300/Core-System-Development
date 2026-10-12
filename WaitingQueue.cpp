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
    addStudent(name, "");
}

void WaitingQueue::addStudent(const string& name, const string& resourceID)
{
    WaitingStudent* newNode = new WaitingStudent(name, resourceID);

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

// Removes the longest-waiting student for one resource (first match in FIFO order).
bool WaitingQueue::removeFirstForResource(const string& resourceID, string& outName)
{
    WaitingStudent* prev = nullptr;
    WaitingStudent* cur = front;

    while (cur != nullptr)
        {
        if (cur->resourceID == resourceID)
            {
            outName = cur->studentName;
            if (prev != nullptr)
                prev->next = cur->next;
            else
                front = cur->next;
            if (cur == rear)
                rear = prev;
            delete cur;
            size--;
            return true;
        }
        prev = cur;
        cur = cur->next;
    }
    return false;
}

int WaitingQueue::countForResource(const string& resourceID) const
{
    int count = 0;
    for (WaitingStudent* cur = front; cur != nullptr; cur = cur->next)
        if (cur->resourceID == resourceID)
            count++;
    return count;
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
        cout << "  " << position << ". " << current->studentName;
        if (!current->resourceID.empty())
            cout << " (waiting for " << current->resourceID << ")";
        cout << endl;
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
