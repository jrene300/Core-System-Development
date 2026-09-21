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
    void removeStudent();
    void displayWaitingList() const;
    bool isEmpty() const;
    int getSize() const;
};

#endif //WAITINGQUEUE_H