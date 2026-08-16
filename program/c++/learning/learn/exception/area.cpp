//
// Created by Administrator on 2026/7/17.
//
#include <string>
#include <iostream>

class MyException : public std::exception {
public:
    explicit MyException(const char *msg) {
        this->msg = new char[strlen(msg) + 1];
        strcpy(this->msg, msg);
    }

    MyException(const MyException &e) {
        this->msg = new char[strlen(e.msg) + 1];
        strcpy(this->msg, e.msg);
        std::cout << "调用了拷贝构造" << std::endl;
    }

    [[nodiscard]] const char *what() const override {
        return this->msg;
    }

    ~MyException() override {
        if (msg)
            delete[] msg;
        msg = nullptr;
        std::cout << "调用了析构函数" << std::endl;
    }

private:
    char *msg;
};

static void func01() {
    //throw直接抛出的异常，该对象是在线程私有的临时缓冲区中开辟的，而不是在函数栈
    //所以异常可以跨函数访问
    throw MyException("出现异常");
}

static void test01() {
    try {
        func01();
    }
    //推荐使用的方式。使用引用去接收临时缓冲区内的异常对象，没有对象的复制开销
    // catch (MyException &e) {
    //     std::cout << e.what() << std::endl;
    // }
    //也可以直接用基类的引用去接收
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    //直接使用变量接收异常，编译器会把缓冲区中的异常对象做一份拷贝给这里的函数栈内局部变量
    //所以会调用该异常类的拷贝构造，如果对象非常大，将增大额外的开销
    // catch (MyException e1) {
    //
    // }
}

// int main() {
//     test01();
//     return 0;
// }
