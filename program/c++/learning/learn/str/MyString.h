//
// Created by Administrator on 2026/7/12.
//

#ifndef LN_MYSTRING_H
#define LN_MYSTRING_H
#include <iostream>
using namespace std;

namespace my_std {
    //自定义string类
    class MyString {
        friend istream &operator>>(istream &is, MyString &str);

        int length;
        char *c_ptr;

    public:
        //构造函数
        MyString();

        MyString(const char *);

        MyString(MyString &);

        ~MyString();

        const char *get_str() const;

        //重载操作符
        char &operator[](int);

        bool operator==(const MyString &) const;

        bool operator!=(const MyString &) const;

        MyString &operator=(const MyString &);

        MyString &operator=(const char *);

        MyString &operator+(const MyString &);

        MyString &operator+=(const MyString &);
    };
}


#endif //LN_MYSTRING_H
