#include <string>
//
// Created by Administrator on 2026/7/13.
//
#include <iostream>
using namespace std;

class Student {
    int age;
    string name;

public:
    Student() : age(0), name(nullptr) {
    };

    ~Student() {
        cout << "~Student()" << endl;
    }

    Student(int age, const string name) : age(age), name(name) {
    }

    Student(Student &student) : age(student.age), name(student.name) {
    }

    void print() {
        cout << this->name << ":" << this->age << endl;
    }
};

class Student2 : public Student {
    double score;

public:
    Student2() : score(0.0f) {
    };

    Student2(int age, const string &name, double score)
        : Student(age, name), score(score) {
    }

    void print() {
        Student::print();
        cout << this->score << endl;
    }

    ~Student2() {
        cout << "~Student2()" << endl;
    }
};

// int main() {
//     Student2 s1(10, "王五", 30.1f);
//     s1.print();
//     return 0;
// }
