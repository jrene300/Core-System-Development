#ifndef WAITINGQUEUE_H
#define WAITINGQUEUE_H

#include "WaitingStudent.h"

class WaitingQueue
{
private:
    WaitingStudent* front;
    WaitingStudent* rear;
    int size;

public:
    WaitingQueue();
    ~WaitingQueue();

    void addStudent(const string& name);
    void addStudent(const string& name, const string& resourceID);
    void removeStudent();
    bool removeFirstForResource(const string& resourceID, string& outName);
    int countForResource(const string& resourceID) const;
    void displayWaitingList() const;
    bool isEmpty() const;
    int getSize() const;
};

#endif //WAITINGQUEUE_H
