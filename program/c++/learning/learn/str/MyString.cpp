//
// Created by Administrator on 2026/7/12.
//


#include "MyString.h"
#include <cstring>

namespace my_std {

    MyString::MyString() : length(0), c_ptr(nullptr) {
    }

    MyString::MyString(const char *str) {
        if (!str) {
            this->length = 0;
            this->c_ptr = nullptr;
        } else {
            this->length = strlen(str);
            this->c_ptr = new char[this->length + 1];
            strcpy(this->c_ptr, str);
        }
    }

    MyString::MyString(MyString &str) : length(str.length) {
        this->c_ptr = new char[this->length + 1];
        strcpy(this->c_ptr, str.c_ptr);
    }

    MyString::~MyString() {
        delete[] this->c_ptr;
        this->length = 0;
        this->c_ptr = nullptr;
    }

    char &MyString::operator[](int offset) {
        if (offset < 0 || offset >= this->length)
            return this->c_ptr[0];
        return this->c_ptr[offset];
    }

    bool MyString::operator==(const MyString &str) const {
        if (this == &str)
            return true;
        if (this->length != str.length)
            return false;
        for (int i = 0; i < this->length; i++) {
            if (this->c_ptr[i] != str.c_ptr[i])
                return false;
        }
        return true;
    }

    MyString &MyString::operator=(const MyString &str) {
        if (this == &str)
            return *this;
        this->length = str.length;
        delete[] this->c_ptr;
        this->c_ptr = new char[this->length + 1];
        strcpy(this->c_ptr, str.c_ptr);
        return *this;
    }

    MyString &MyString::operator=(const char *str) {
        this->length = strlen(str);
        delete[] this->c_ptr;
        this->c_ptr = new char[this->length + 1];
        strcpy(this->c_ptr, str);
        return *this;
    }

    MyString &MyString::operator+(const MyString &str) {
        MyString *result = new MyString;
        result->length = this->length + str.length;
        result->c_ptr = new char[result->length + 1];
        strcpy(result->c_ptr, this->c_ptr);
        strcat(result->c_ptr, str.c_ptr);
        return *result;
    }

    const char *MyString::get_str() const {
        return this->c_ptr;
    }

    bool MyString::operator!=(const MyString &str) const {
        return !(*this == str);
    }

    MyString &MyString::operator+=(const MyString &str) {
        this->length += str.length;
        char *temp = new char[this->length + 1];
        strcpy(temp, this->c_ptr);
        strcat(temp, str.c_ptr);
        delete[] this->c_ptr;
        this->c_ptr = temp;
        return *this;
    }

};
//
// ostream &operator<<(std::ostream &os, const MyString &str) {
//     os << str.get_str();
//     return os;
// }
//
// //重载标准输入流操作符>>
// istream &operator>>(istream &is, MyString &str) {
//     char temp[1024]{0}, ch;
//     int count = 0;
//     while (is.get(ch)) {
//         temp[count++] = ch;
//         if (ch == '\n')
//             break;
//     }
//     str.length = count;
//     delete[] str.c_ptr;
//     str.c_ptr = new char[count + 1];
//     strcpy(str.c_ptr, temp);
//     return is;
// };
// int main() {
//     // MyString str1("123"), str2(str1), str3;
//     // // cout << str1 << endl;
//     // // cout << str2 << endl;
//     // // str3 = "hello world";
//     // // cout << str3 << endl;
//     // //
//     // // cout << str3 + str2 + str1 << endl;
//     // //
//     // // str3[2] = 'w';
//     // // cout << str3 << endl;
//     // // // str3 = "123";
//     // // // cout << (str3 == str2) << endl;
//     // // // str3 = str2;
//     // // // cout << str3 << endl;
//     // // str1 += str3;
//     // // cout << str1 << endl;
//     // cout << "请输入字符串:" << endl;
//     // cin >> str1;
//     // cout << "输入的字符串为：" << str1 << endl;
//     string s1 = "123", s2 = "124";
//     cout << (s1 == s2) << endl;
//     return 0;
// }
