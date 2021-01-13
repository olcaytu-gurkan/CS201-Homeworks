//Olcaytu Gürkan 21903031 Section 2
#include "Book.h"
#include <iostream>

Book::Book() {
    id = 0;
    year = 0;
    title = "";
    isChecked = false;
}

Book::Book(int bookId, int bookYear, string bookTitle) {
    id = bookId;
    year = bookYear;
    title = bookTitle;
    isChecked = false;
}

Book::~Book() {
    id = 0;
    year = 0;
    title = "";
    isChecked = false;
}

int Book::getId() {
    return id;
}

int Book::getYear() {
    return year;
}

string Book::getTitle() {
    return title;
}

void Book::setId(int bookId) {
    id = bookId;
}

void Book::setYear(int bookYear) {
    year = bookYear;
}

void Book::setTitle(string bookTitle) {
    title = bookTitle;
}

bool Book::getCheckValue() {
    return isChecked;
}

void Book::check(bool truthVal) {
    if (truthVal)
        isChecked = true;
    else {
        isChecked = false;
        cout << "Book " << id << " has been returned" << endl;
    }
}

int Book::getOwnerId() {
    return ownerId;
}

void Book::setOwnerId(int id) {
    ownerId = id;
}
