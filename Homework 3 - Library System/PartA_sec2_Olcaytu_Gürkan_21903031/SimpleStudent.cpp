//Olcaytu Gürkan 21903031 Section 2
#include <iostream>
#include <stdlib.h>
using namespace std;
#include "SimpleStudent.h"

Student::Student() {
    id = 0;
    name = "";
}

Student::Student(int studentId, string studentName) {
    id = studentId;
    name = studentName;
}

Student::~Student() {
    id = 0;
    name = "";
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
