#ifndef SYSTEM_H
#define SYSTEM_H

#include "Student.h"
#include "Faculty.h"
#include "LazyBST.hpp"
#include <fstream>

class System {
    public:
        System();
        ~System();
    private:
        LazyBST<Student> *studentTable;
        LazyBST<Faculty> *facultyTable;

        void ShowMenu();
        int GetChoice();
        void MakeChoice(int choice);
        void RunProgram();

        void PrintStudentsInOrder(TreeNode<Student>* node);
        void PrintFacultyInOrder(TreeNode<Faculty>* node);
        void FindStudent();
        void FindFaculty();
        void AddNewStudent();
        void DeleteStudent();
        void AddNewFaculty();
        void DeleteFaculty();
        void ChangeAdvisor();
        void RemoveAdvisee();

        void UpdateAdviseeIDList(int studentID, int advisorID);
};

#endif