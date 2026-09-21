#include "WaitingStudent.h"

WaitingStudent::WaitingStudent(const string& name)
{
    studentName = name;
    next = nullptr;
}