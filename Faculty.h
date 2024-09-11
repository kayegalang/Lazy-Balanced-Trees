#ifndef FACULTY_H
#define FACULTY_H

#include <iostream>
using namespace std;
#include "LinkedList.hpp"

class Faculty {
    public:
        Faculty();
        Faculty(int facultyID, string name, string level, string department);
        ~Faculty();

        void PrintFacultyInformation();

        void AddToList(int studentID);
        void RemoveFromList(int studentID);
    private:
        int facultyID;
        string name;
        string level;
        string department;

        LinkedList<int> *adviseeIDList;
};

#endif