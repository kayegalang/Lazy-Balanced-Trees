#include "Faculty.h"

// Default constructor
Faculty::Faculty() {
    // Initialize member variables
    facultyID = 0;
    name = "";
    level = "";
    department = "";

    // Initialize advisee ID list to nullptr
    adviseeIDList = nullptr;
}

// Parameterized constructor
Faculty::Faculty(int facultyID, string name, string level, string department) {
    // Initialize member variables with provided values
    this->facultyID = facultyID;
    this->name = name;
    this->level = level;
    this->department = department;

    // Create a new linked list for the advisee ID list
    adviseeIDList = new LinkedList<int>;
}

// Destructor
Faculty::~Faculty() {
    // Destructor implementation is empty as the LinkedList destructor will handle cleanup
}

// Print faculty information
void Faculty::PrintFacultyInformation() {
    // Print faculty details
    cout << "Faculty ID: " << facultyID << endl;
    cout << "Name: " << name << endl;
    cout << "Level: " << level << endl;
    cout << "Department: " << department << endl;
    cout << "Advisee ID List: ";
    // Print advisee ID list using linked list print method
    adviseeIDList->printList(false);
    cout << endl;
}

// Add student ID to the advisee ID list
void Faculty::AddToList(int studentID) {
    adviseeIDList->insertBack(studentID);
}

// Remove student ID from the advisee ID list
void Faculty::RemoveFromList(int studentID) {
    adviseeIDList->removeNode(studentID);
}