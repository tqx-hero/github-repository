//
// Created by Administrator on 2026/7/7.
//
#include <string>
#include <iostream>
using namespace std;

struct stu {
    int id;
    int age;
    string name;
};

void readStuInfo(stu &s) {
    //18 years old Jack's school id is 1.
    cout << s.age << " years old " << s.name << "'s school id is " << s.id << "." << endl;
}

int main() {
    return 0;
}
