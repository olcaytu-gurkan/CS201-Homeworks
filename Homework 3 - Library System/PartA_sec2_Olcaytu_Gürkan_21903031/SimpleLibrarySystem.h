//Olcaytu Gürkan 21903031 Section 2
#ifndef SIMPLELIBRARYSYSTEM_H_INCLUDED
#define SIMPLELIBRARYSYSTEM_H_INCLUDED
#include "SimpleStudent.h"
#include <stdlib.h>
using namespace std;

class LibrarySystem {
public:
    LibrarySystem();
    ~LibrarySystem();

    void addStudent(const int studentId, const string studentName);
    void deleteStudent(const int studentId);

    void showStudent(const int studentId) const;
    void printList() const;

private:
    struct StudentNode {
        Student item;
        StudentNode* next;
    };

    int size;
    StudentNode* head;
    bool doesExist(const int studentId) const;

};
#endif // SIMPLELIBRARYSYSTEM_H_INCLUDED
