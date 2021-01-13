//Olcaytu Gürkan 21903031 Section 2
#include <iostream>
#include "LibrarySystem.h"

LibrarySystem::LibrarySystem() {
    size = 0;
    bookSize = 0;
    head = NULL;
    bookHead = NULL;
}

LibrarySystem::~LibrarySystem() {
    size = 0;
    bookSize = 0;
    StudentNode* prev = head;
    while (head != NULL) {
        head = head->next;
        delete prev; //cleaning the list
        prev = head;
    }
    delete prev;
    delete head;

    BookNode* bprev = bookHead;
    while (bookHead != NULL) {
        bookHead = bookHead->next;
        delete bprev; //cleaning the list
        bprev = bookHead;
    }
    delete bprev;
    delete bookHead;
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

void LibrarySystem::addBook(const int bookId, const string bookName, const int bookYear) {
    if (doesBookExist(bookId))
        cout << "Book " << bookId << " already exists" << endl;
    else if (bookId <= 0)
        cout << "Error, invalid id." << endl;
    else {
        BookNode* newNode = new BookNode;
        newNode->item = Book(bookId, bookYear, bookName);
        newNode->next = NULL;
        if (bookHead == NULL) {
            bookHead = newNode;
        }
        else {
            BookNode* cur = bookHead;
            while (cur->next != NULL) {
                cur = cur->next;
            }
            cur->next = newNode;
            cur = NULL;
            delete cur;
        }
        size++;
        cout << "Book " << bookId << " has been added" << endl;
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
            BookNode* bcur = bookHead;
            while (bcur != NULL) {
                if ((bcur -> item).getOwnerId() == (prev->item).getId()) {
                    (bcur->item).check(false);
                }
                bcur = bcur->next;
            }
            bcur = NULL;
            delete bcur;
            cur->next = cur->next->next;
            cur = NULL;
            delete prev;
            delete cur;
        }
        cout << "Student " << studentId << " has been deleted" << endl;
        size--;
    }
}

void LibrarySystem::deleteBook(const int bookId) {
    if (!doesBookExist(bookId))
        cout << "Book " << bookId << " does not exist" << endl;
    else {
        returnBook(bookId);
        if ((bookHead->item).getId() == bookId) {
            BookNode* prev = bookHead;
            bookHead = bookHead->next;
            delete prev;
        }
        else {
            BookNode* cur = bookHead;
            while ((cur->next->item).getId() != bookId) {
                cur = cur->next;
            }
            BookNode * prev;
            prev = cur->next;
            cur->next = cur->next->next;
            cur = NULL;
            delete prev;
            delete cur;
        }
        cout << "Book " << bookId << " has been deleted" << endl;
        size--;
    }
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

bool LibrarySystem::doesBookExist(const int bookId) const {
    BookNode* cur = bookHead;
    while (cur != NULL) {
        if ((cur -> item).getId() == bookId)
            return true;
        cur = cur->next;
    }
    cur = NULL;
    delete cur;
    return false;
}

void LibrarySystem::checkoutBook(const int bookId, const int studentId) {
    if (!doesBookExist(bookId))
        cout << "Book " << bookId << " does not exist for checkout" << endl;
    else if (!doesExist(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        BookNode* cur = bookHead;
        int idOfBook;
        bool found = false;
        int yearOfBook;
        string titleOfBook;
        while (cur != NULL) {
            if ((cur -> item).getId() == bookId && !((cur->item).getCheckValue())) {
                (cur->item).check(true);
                idOfBook = (cur -> item).getId();
                yearOfBook = (cur -> item).getYear();
                titleOfBook = (cur -> item).getTitle();
                StudentNode* sCur = head;
                while (sCur != NULL) {
                    if ((sCur -> item).getId() == studentId) {
                        (sCur -> item).addSBook(idOfBook, titleOfBook, yearOfBook);
                        (cur -> item).setOwnerId(studentId);
                        found = true;
                    }

                    sCur = sCur->next;
                }
                sCur = NULL;
                delete sCur;
            }
            cur = cur->next;
        }
        if (found)
            cout << "Book " << bookId << " has been checked out by student " << studentId << endl;
        else
            cout << "Book " << bookId << " has been already checked out by another student" << endl;
        cur = NULL;
        delete cur;
    }
}

void LibrarySystem::returnBook(const int bookId) {
    if (!doesBookExist(bookId))
        cout << "Book " << bookId << " does not exist" << endl;
    else {
        BookNode* cur = bookHead;
        while (cur != NULL) {
            if ((cur -> item).getId() == bookId) {
                if ((cur -> item).getCheckValue()) {
                    (cur->item).check(false);
                    int stuId = (cur->item).getOwnerId();
                    StudentNode* sCur = head;
                    while (sCur != NULL) {
                        if ((sCur -> item).getId() == stuId) {
                            (sCur -> item).returnSBook(bookId);
                        }
                        sCur = sCur->next;
                    }
                    sCur = NULL;
                    delete sCur;
                    //cout << "Book " << bookId << " has been returned" << endl;
                }
                else {
                    cout << "Book " << bookId << " has not been checked out" << endl;
                }
            }
            cur = cur->next;
        }
        cur = NULL;
        delete cur;
    }
}

void LibrarySystem::showAllBooks() const {
    cout << "Book id         Book name                                    Year         Status" << endl;
    BookNode* cur = bookHead;
    bool print = false;
    while (cur != NULL) {
        int titleLen = (cur->item).getTitle().length();
        string noOfSpace = "";
        for (int i = 0; i < 45 - titleLen; i++) {//45 is the space that I used for headers
            noOfSpace = noOfSpace + " ";
        }
        cout << (cur -> item).getId() << "            " << (cur->item).getTitle() << noOfSpace <<
        (cur->item).getYear() << "         ";
        string statusString = "";

        if ((cur->item).getCheckValue()) {
            print = true;
            statusString = "Checked out by student ";
        }
        else {

            statusString = "Not checked out";
        }
        cout << statusString;
        if (print)
            cout << (cur->item).getOwnerId();
        cur = cur->next;
        cout << endl;
    }
    cur = NULL;
    delete cur;
}

void LibrarySystem::showBook(const int bookId) const {
    if (doesBookExist(bookId)) {
        BookNode* cur = bookHead;
        bool print = false;
        while (cur != NULL) {
            if ((cur -> item).getId() == bookId) {
                int titleLen = (cur->item).getTitle().length();
                string noOfSpace = "";
                for (int i = 0; i < 45 - titleLen; i++) {//45 is the space that I used for headers
                    noOfSpace = noOfSpace + " ";
                }
                cout << (cur -> item).getId() << "            " << (cur->item).getTitle() << noOfSpace <<
                (cur->item).getYear() << "         ";
                string statusString = "";

                if ((cur->item).getCheckValue()) {
                    print = true;
                    statusString = "Checked out by student ";
                }
                else {

                    statusString = "Not checked out";
                }
                cout << statusString;
                if (print)
                    cout << (cur->item).getOwnerId();
            }
            cur = cur->next;
        }
        cur = NULL;
        delete cur;
        cout << endl;
    }
    else {
        cout << "Book " << bookId << " does not exist" << endl;
    }
}

void LibrarySystem::showStudent(const int studentId) const {
    if(!doesExist(studentId))
        cout << "Student " << studentId << " does not exist" << endl;
    else {
        StudentNode* sCur = head;
        while (sCur != NULL) {
            if ((sCur -> item).getId() == studentId) {
                cout << "Student id: " << (sCur->item).getId() << " Student Name: " << (sCur->item).getName() << endl;
                if ((sCur -> item).isEmpty())
                    cout << "Student " << studentId << " has no books" << endl;
                else {
                    BookNode* cur = bookHead;
                    cout << "Student " << studentId << " has checked out the following books:" << endl;
                    cout << "Book id         Book name                                    Year" << endl;
                    while (cur != NULL) {
                        if ((cur -> item).getOwnerId() == studentId) {
                            int titleLen = (cur->item).getTitle().length(); //finding number of space
                            string noOfSpace = "";
                            for (int i = 0; i < 45 - titleLen; i++) { //45 is the space that I used for headers
                                noOfSpace = noOfSpace + " ";
                            }
                            cout << (cur -> item).getId() << "            " << (cur->item).getTitle() << noOfSpace <<
                            (cur->item).getYear() << endl;
                        }
                        cur = cur->next;
                    }
                    cur = NULL;
                    delete cur;
                    cout << endl;
                }
            }
            sCur = sCur->next;
        }
        sCur = NULL;
        delete sCur;
    }
}
