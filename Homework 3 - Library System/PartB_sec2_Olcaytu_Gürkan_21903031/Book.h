//Olcaytu Gürkan 21903031 Section 2
#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED
#include <string>
using namespace std;

class Book {
public:
    Book();
    Book(int bookId, int bookYear, string bookTitle);
    ~Book();
    int getId();
    int getYear();
    string getTitle();
    void setId(int bookId);
    void setYear(int bookYear);
    void setTitle(string bookTitle);
    bool getCheckValue();
    void check(bool);
    void setOwnerId(int);
    int getOwnerId();

private:
    int id;
    int year;
    int ownerId;
    string title;
    bool isChecked;
};

#endif // BOOK_H_INCLUDED
