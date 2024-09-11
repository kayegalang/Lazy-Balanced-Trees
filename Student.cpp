#include "Student.h"

// Default constructor
Student::Student() {
    // Initialize member variables to default values
    studentID = 0;
    name = "";
    level = "";
    major = "";
    GPA = 0.0;
    advisorID = 0;
}

// Parameterized constructor
Student::Student(int studentID, string name, string level, string major, double GPA, int advisorID) {
    // Initialize member variables with provided values
    this->studentID = studentID;
    this->name = name;
    this->level = level;
    this->major = major;
    this->GPA = GPA;
    this->advisorID = advisorID;
}

// Destructor
Student::~Student() {
    // Destructor implementation is empty
}

// Print student information
void Student::PrintStudentInformation() {
    // Print student details
    cout << "Student ID: " << studentID << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl;
    cout << "Major: " << major << endl;
    cout << "GPA: " << GPA << endl;
    cout << "Advisor ID: " << advisorID << endl;
    cout << endl;
}

// Change student's advisor
void Student::ChangeAdvisor(int facultyID) {
    // Update the advisor ID
    advisorID = facultyID;
}

// Get student's advisor ID
int Student::GetAdvisorID() {
    // Return the advisor ID
    return advisorID;
}
