#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
using namespace std;

class Student {
    public:
        Student();
        Student(int studentID, string name, string level, string major, double GPA, int advisorID);
        ~Student();

        void PrintStudentInformation();
        void ChangeAdvisor(int facultyID);
        int GetAdvisorID();
    private:
        int studentID;
        string name;
        string level;
        string major;
        double GPA;
        int advisorID;
};  

#endif