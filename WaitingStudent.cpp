#include "WaitingStudent.h"

WaitingStudent::WaitingStudent(const string& name)
{
    studentName = name;
    resourceID = "";
    next = nullptr;
}

WaitingStudent::WaitingStudent(const string& name, const string& resID)
{
    studentName = name;
    resourceID = resID;
    next = nullptr;
}
