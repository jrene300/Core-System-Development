#ifndef WAITINGSTUDENT_H
#define WAITINGSTUDENT_H

#include <string>
using namespace std;

class WaitingStudent
{
public:
    string studentName;
    string resourceID;
    WaitingStudent* next;

    WaitingStudent(const string& name);
    WaitingStudent(const string& name, const string& resID);
};

#endif //WAITINGSTUDENT_H