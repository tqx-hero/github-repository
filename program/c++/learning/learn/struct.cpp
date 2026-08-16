//
// Created by Administrator on 2026/7/8.
//
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int age;
    double score;

    Student() : name(""), age(0), score(0.00f) {
    }

    Student(const string &name, int age, double score = 0.00f)
        : name(name),
          age(age),
          score(score) {
        cout << "初始化函数被调用" << endl;
    }

    Student(const Student &stu) : name(stu.name), age(stu.age), score(stu.score) {
        cout << "拷贝函数被调用" << endl;
    }

    void operator=(const Student &student) {
        cout << "重载运算符被调用" << endl;
        this->name = student.name;
        this->age = student.age;
        this->score = student.score;
    }
};

// int main() {
//     //调用的构造函数进行初始化
//     Student stu1{"张三", 20, 99.5f};
//     //语义上是等号右边先调用构造函数生成一个临时对象，然后在调用拷贝构造函数给stu2赋值
//     //但是在编译期间，编译器对其进行优化，使得这条语句不再生成临时对象，直接初始化stu2，然后对其进行赋值
//     //所以行为上与上面的直接初始化相同，但是语义上截然不同。
//     Student stu2 = {"李四", 21, 88.4f};
//     //调用拷贝构造函数进行初始化操作
//     Student stu3(stu1);
//     //调用重载运算符= ，对数据进行赋值操作，如果没有重载运算符，会使用默认的=
//     stu3 = stu2;
//     return 0;
// }
