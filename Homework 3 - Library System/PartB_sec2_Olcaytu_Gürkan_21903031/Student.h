//Olcaytu Gürkan 21903031 Section 2
#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include "Book.h"
using namespace std;

class Student {
public:
    Student();
    Student(int studentId, string studentName);
    ~Student();
    int getId();
    string getName();
    void setId(int);
    void setName(string);
    void addSBook(const int bookId, const string bookName, const int bookYear);
    void returnSBook(const int bookId);
    bool isEmpty();

private:
    struct StudentsBookNode {
        Book item;
        StudentsBookNode* next;
    };

    int size;
    StudentsBookNode* head;
    bool doesExist(const int bookId) const;
    int id;
    string name;
};


#endif // STUDENT_H_INCLUDED
