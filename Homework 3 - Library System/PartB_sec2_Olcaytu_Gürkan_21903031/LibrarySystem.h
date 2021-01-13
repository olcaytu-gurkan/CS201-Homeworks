//Olcaytu Gürkan 21903031 Section 2
#ifndef LIBRARYSYSTEM_H_INCLUDED
#define LIBRARYSYSTEM_H_INCLUDED
#include "Student.h"
#include <stdlib.h>
using namespace std;

class LibrarySystem {
public:
    LibrarySystem();
    ~LibrarySystem();

    void addBook(const int bookId, const string bookName, const int bookYear);
    void deleteBook(const int bookId);

    void addStudent(const int studentId, const string studentName);
    void deleteStudent(const int studentId);

    void checkoutBook(const int bookId, const int studentId);
    void returnBook(const int bookId);

    void showAllBooks() const;
    void showBook(const int bookId) const;
    void showStudent(const int studentId) const;

private:
    struct StudentNode {
        Student item;
        StudentNode* next;
    };

    int size; // size is not used in this program, but initiliazed for the possible future use
    StudentNode* head;
    bool doesExist(const int studentId) const;

    struct BookNode {
        Book item;
        BookNode* next;
    };
    BookNode* bookHead;
    bool doesBookExist(const int bookId) const;
    int bookSize;
};
#endif // LIBRARYSYSTEM_H_INCLUDED
