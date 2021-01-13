//Olcaytu Gürkan 21903031 Section 2
#include <iostream>
using namespace std;
#include "SimpleLibrarySystem.h"

LibrarySystem::LibrarySystem() {
    size = 0;
    head = NULL;
}

LibrarySystem::~LibrarySystem() {
    size = 0;
    StudentNode* prev = head;
    while (head != NULL) {
        head = head->next;
        delete prev; //cleaning the list
        prev = head;
    }
    delete prev;
    delete head;
}

void LibrarySystem::addStudent(const int studentId, const string studentName) {
    if (doesExist(studentId))
        cout << "Student " << studentId << " already exists" << endl;
    else if (studentId <= 0)
        cout << "Error, invalid id." << endl;
    else {
        StudentNode* newNode = new StudentNode;
        newNode->item = Student(studentId, studentName);
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
        }
        else {
            StudentNode* cur = head;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = newNode;
            cur = NULL;
            delete cur;
        }
        size++;
        cout << "Student " << studentId << " has been added" << endl;
        newNode = NULL;
        delete newNode;
    }
}

void LibrarySystem::deleteStudent(const int studentId) {
    if (!doesExist(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        if ((head->item).getId() == studentId) {
            StudentNode* prev = head;
            head = head->next;
            delete prev;
        }
        else {
            StudentNode* cur = head;
            while ((cur->next->item).getId() != studentId) {
                cur = cur->next;
            }
            StudentNode * prev;
            prev = cur->next;
            cur->next = cur->next->next;
            cur = NULL;
            delete prev;
            delete cur;
        }
        cout << "Student " << studentId << " has been deleted" << endl;
        size--;
    }
}

void LibrarySystem::showStudent(const int studentId) const {
    if (!doesExist(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        StudentNode* cur = head;
        while (cur != NULL) {
            if ((cur->item).getId() == studentId) {
                cout << "Student id: " << studentId << " Student name: " << (cur->item).getName() << endl;
                break;
            }
            cur = cur->next;
        }
        cur = NULL;
        delete cur;
    }
}

void LibrarySystem::printList() const {
    StudentNode* cur = head;
    while (cur != NULL) {
        cout << (cur->item).getId() << " ";
        cur = cur->next;
    }
    cur = NULL;
    delete cur;
    cout << endl;
}

bool LibrarySystem::doesExist(const int studentId) const {
    StudentNode* cur = head;
    while (cur != NULL) {
        if ((cur -> item).getId() == studentId)
            return true;
        cur = cur->next;
    }
    cur = NULL;
    delete cur;
    return false;
}
