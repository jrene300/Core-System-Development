#ifndef WAITINGSTUDENT_H
#define WAITINGSTUDENT_H

#include <string>
using namespace std;

class WaitingStudent
{
public:
    string studentName;
    WaitingStudent* next;

    WaitingStudent(const string& name);
};

#endif //WAITINGSTUDENT_H
