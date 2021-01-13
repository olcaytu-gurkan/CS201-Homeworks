//Olcaytu Gürkan 21903031 Section 2
#ifndef SIMPLESTUDENT_H_INCLUDED
#define SIMPLESTUDENT_H_INCLUDED

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

private:
    int id;
    string name;
};


#endif // SIMPLESTUDENT_H_INCLUDED

