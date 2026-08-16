//
// Created by Administrator on 2026/7/9.
//
#include <iostream>
using namespace std;

class Student {
public:
    string name;
    int age;
    double score;
    //可以设置初始化默认值，但是在设置时必须从右往左设置，不能出现左边有默认值但中间没有的情况
    Student(string name = "", int age = 0, double score = 0.00f) : name(name), age(age), score(score) {
    }
};

// int main() {
//
//     Student stu{"张三"};
//
//     return 0;
// }
