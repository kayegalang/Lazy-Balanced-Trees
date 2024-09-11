#include "System.h"

// Default constructor
System::System() {
    // Initialize student and faculty tables
    studentTable = new LazyBST<Student>;
    facultyTable = new LazyBST<Faculty>;

    // Run the program
    RunProgram();
}

// Destructor
System::~System() {
    // Delete student and faculty tables to free memory
    delete studentTable;
    delete facultyTable;
}

// Display menu options
void System::ShowMenu() {
    // Display menu options for the user
    cout << "====================================MENU===================================" << endl;
    cout << "1. Print all students and their information (sorted by ascending id #) " << endl;
    cout << "2. Print all faculty and their information (sorted by ascending id #) " << endl;
    cout << "3. Find and display student information given the student id " << endl;
    cout << "4. Find and display faculty information given the faculty id " << endl;
    cout << "5. Add a new student " << endl;
    cout << "6. Delete a student given the id " << endl;
    cout << "7. Add a new faculty member " << endl;
    cout << "8. Delete a faculty member given the id " << endl;
    cout << "9. Change a student's advisor given the student id and the new faculty id " << endl;
    cout << "10. Remove an advisee from a faculty member given the ids " << endl;
    cout << "11. Exit" << endl;
    cout << "===========================================================================" << endl;
}

// Get user's choice
int System::GetChoice() {
    int choice;
    // Prompt user to enter a choice and validate input
    cout << "Enter an int corresponding to the choice you want to make: ";
    cin >> choice;
    while(choice > 11 || choice < 1) {
        cout << "Incorrect choice, try again." << endl;
        cout << "Enter an int corresponding to the choice you want to make: ";
        cin >> choice;
    }
    return choice;
}

// Run the program
void System::RunProgram() {
    // Display menu and get user's choice
    ShowMenu();
    int choice = GetChoice();
    // Continue running program until user chooses to exit (choice 11)
    while(choice != 11) {
        // Perform action based on user's choice
        MakeChoice(choice);
        // Display menu again and get user's choice
        ShowMenu();
        choice = GetChoice();
    }
    cout << "Goodbye!" << endl;
    // Open a log file to write program output
    ofstream outputFile("runLog.txt");
    // Check if the file is opened successfully
    if (!outputFile) {
        cerr << "Error: Unable to open file." << endl;
        exit(1); // Exit program with error code
    }
    // Redirect standard output to the file
    streambuf* coutBuf = cout.rdbuf(); // Save old buffer
    cout.rdbuf(outputFile.rdbuf()); // Redirect std::cout to outputFile
    // Print all students and faculty in order to the log file
    PrintStudentsInOrder(studentTable->root);
    PrintFacultyInOrder(facultyTable->root);
    // Restore standard output
    cout.rdbuf(coutBuf); // Restore old buffer
    // Close the file
    outputFile.close();
}

// Perform action based on user's choice
void System::MakeChoice(int choice) {
    switch(choice) {
        case 1:
            PrintStudentsInOrder(studentTable->root);
            break;
        case 2:
            PrintFacultyInOrder(facultyTable->root);
            break;
        case 3:
            FindStudent();
            break;
        case 4:
            FindFaculty();
            break;
        case 5:
            AddNewStudent();
            break;
        case 6:
            DeleteStudent();
            break; 
        case 7:
            AddNewFaculty();
            break;
        case 8:
            DeleteFaculty();
            break;
        case 9:
            ChangeAdvisor();
            break;
        case 10:
            RemoveAdvisee();
            break;
    }
}

// Print students in order
void System::PrintStudentsInOrder(TreeNode<Student>* node) {
    if(node == nullptr) 
        return;
    
    // Recursively print students in order
    PrintStudentsInOrder(node->left);
    node->value.PrintStudentInformation();
    PrintStudentsInOrder(node->right);
}

// Print faculty in order
void System::PrintFacultyInOrder(TreeNode<Faculty>* node) {
    if(node == nullptr) 
        return;
    
    // Recursively print faculty in order
    PrintFacultyInOrder(node->left);
    node->value.PrintFacultyInformation();
    PrintFacultyInOrder(node->right);
}

// Find and display student information
void System::FindStudent() {
    int studentID;
    cout << "Enter student ID to find: ";
    cin >> studentID;
    // Print student information using studentTable
    studentTable->getValue(studentID).PrintStudentInformation();
}

// Find and display faculty information
void System::FindFaculty() {
    int facultyID;
    cout << "Enter faculty ID to find: ";
    cin >> facultyID;
    // Print faculty information using facultyTable
    facultyTable->getValue(facultyID).PrintFacultyInformation();
}

// Add a new student
void System::AddNewStudent() {
    // Prompt user for student information
    int studentID;
    string name;
    string level;
    string major;
    double GPA;
    int advisorID;

    cout << "Enter student ID: ";
    cin >> studentID;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter level: ";
    cin >> level;
    cout << "Enter major: ";
    cin >> major;
    cout << "Enter GPA: ";
    cin >> GPA;
    cout << "Enter advisor ID: ";
    cin >> advisorID;

    // Create new student object and add to studentTable
    Student newStudent(studentID, name, level, major, GPA, advisorID);
    studentTable->insert(studentID, newStudent);

    // Update faculty advisee ID list
    UpdateAdviseeIDList(studentID, advisorID);
}

// Update faculty advisee ID list
void System::UpdateAdviseeIDList(int studentID, int advisorID) {
    facultyTable->getValue(advisorID).AddToList(studentID);
}

// Delete a student
void System::DeleteStudent() {
    int studentID;
    // Prompt user for student ID to delete
    cout << "Enter the ID of the student to be deleted: ";
    cin >> studentID;
    // Check if student exists and delete if found
    if(studentTable->contains(studentID)) {
        studentTable->deleteNode(studentID);
        cout << "Student deleted" << endl;
    }
    else {
        cout << "No student found, try a different choice." << endl;
    }
}

// Add a new faculty member
void System::AddNewFaculty() {
    // Prompt user for faculty information
    int facultyID;
    string name;
    string level;
    string department;

    cout << "Enter faculty ID: ";
    cin >> facultyID;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter level: ";
    cin >> level;
    cout << "Enter department: ";
    cin >> department;

    // Create new faculty object and add to facultyTable
    Faculty newFaculty(facultyID, name, level, department);
    facultyTable->insert(facultyID, newFaculty);
}

// Delete a faculty member
void System::DeleteFaculty() {
    int facultyID;
    // Prompt user for faculty ID to delete
    cout << "Enter the ID of the faculty to be deleted: ";
    cin >> facultyID;
    // Check if faculty exists and delete if found
    if(facultyTable->contains(facultyID)) {
        facultyTable->deleteNode(facultyID);
        cout << "Faculty deleted" << endl;
    }
    else {
        cout << "No faculty found, try a different choice." << endl;
    }
}

// Change a student's advisor
void System::ChangeAdvisor() {
    int studentID;
    int facultyID;
    // Prompt user for student ID and new faculty ID
    cout << "Enter ID of the student whose advisor you want to change: ";
    cin >> studentID;
    cout << "Enter the ID of the faculty to be their new advisor: ";
    cin >> facultyID;

    // Update student's advisor and faculty's advisee list
    int previousAdvisor = studentTable->getValue(studentID).GetAdvisorID();
    studentTable->getValue(studentID).ChangeAdvisor(facultyID);
    facultyTable->getValue(previousAdvisor).RemoveFromList(studentID);
    UpdateAdviseeIDList(studentID, facultyID);
}

// Remove an advisee from a faculty member
void System::RemoveAdvisee() {
    int facultyID;
    int studentID;
    // Prompt user for faculty ID and student ID
    cout << "Enter ID of the faculty whose advisee you want to remove: ";
    cin >> facultyID;
    cout << "Enter ID of the advisee you want to remove: ";
    cin >> studentID;

    // Remove student from faculty's advisee list
    facultyTable->getValue(facultyID).RemoveFromList(studentID);
}
