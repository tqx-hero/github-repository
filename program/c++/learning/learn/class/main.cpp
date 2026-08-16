//
// Created by Administrator on 2026/7/10.
//
#include <iostream>
using namespace std;
//类的默认访问权限是private
class Student {
    string name;
    int sex;

public:
    Student(const string &name, int sex)
        : name(name),
          sex(sex) {
    }

    void print() {
        cout << "name = " << this->name << ",sex = " << sex << endl;
    }
};
//默认权限为public
struct StudentS {
private:
    string name;
    int sex;
public:
    StudentS(const string &name, int sex)
        : name(name),
          sex(sex) {
    }

    void print() {
        cout << "name = " << this->name << ",sex = " << sex << endl;
    }

    ~StudentS() {
        cout << "析构函数被调用" << endl;
    };
};
//
// int main() {
//     Student stu{"张三", 1};
//     stu.print();
//
//     StudentS stus{"里斯", 2};
//     stus.print();
//
//     return 0;
// }
