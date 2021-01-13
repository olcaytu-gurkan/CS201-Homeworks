//Olcaytu Gürkan 21903031 Section 2
#include "Student.h"
#include <iostream>
#include <stdlib.h>


Student::Student() {
    id = 0;
    name = "";
    head = NULL;
}

Student::Student(int studentId, string studentName) {
    id = studentId;
    name = studentName;
    head = NULL;
}

Student::~Student() {
    id = 0;
    name = "";
    StudentsBookNode* prev = head;
    while (head != NULL) {
        head = head->next;
        delete prev; //cleaning the list
        prev = head;
    }
    delete prev;
    delete head;
}

int Student::getId() {
    return id;
}

string Student::getName() {
    return name;
}

void Student::setId(int newId) {
    id = newId;
}

void Student::setName(string newName) {
    name = newName;
}

bool Student::doesExist(const int bookId) const {
    StudentsBookNode* cur = head;
    while (cur != NULL) {
        if ((cur -> item).getId() == bookId)
            return true;
        cur = cur->next;
    }
    cur = NULL;
    delete cur;
    return false;
}

void Student::addSBook(const int bookId, const string bookName, const int bookYear) {
    if (doesExist(bookId))
        cout << "Book " << bookId << " already exists" << endl;
    else if (bookId <= 0)
        cout << "Error, invalid id." << endl;
    else {
        StudentsBookNode* newNode = new StudentsBookNode;
        newNode->item = Book(bookId, bookYear, bookName);
        newNode->next = NULL;
        if (head == NULL) {
            head = newNode;
        }
        else {
            StudentsBookNode* cur = head;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = newNode;
            cur = NULL;
            delete cur;
        }
        size++;
        //cout << "Book " << bookId << " has been added" << endl;
        newNode = NULL;
        delete newNode;
    }
}

void Student::returnSBook(const int bookId) {
    //if (!doesExist(bookId))
        //cout << "Book " << bookId << " does not exist" << endl;
    if (doesExist(bookId)) {
        if ((head->item).getId() == bookId) {
            StudentsBookNode* prev = head;
            head = head->next;
            delete prev;
        }
        else {
            StudentsBookNode* cur = head;
            while ((cur->next->item).getId() != bookId) {
                cur = cur->next;
            }
            StudentsBookNode * prev;
            prev = cur->next;
            cur->next = cur->next->next;
            cur = NULL;
            delete prev;
            delete cur;
        }
        //cout << "Book " << bookId << " has been deleted" << endl;
        size--;
    }
}

bool Student::isEmpty() {
    return (head == NULL);
}
