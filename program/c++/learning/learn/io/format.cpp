//
// Created by Administrator on 2026/7/18.
//
#include <iomanip>
#include <iostream>
//通过成员函数形式设置格式
static inline void test01() {
    using namespace std;
    int number = 10, count = 20;
    cout.setf(ios::showbase);
    cout.unsetf(ios::dec); //停止使用十进制输出格式
    cout.setf(ios::oct); //改用八进制输出格式
    cout << number << endl;
    cout << count << endl;
    //按照十六进制输出
    cout.flags(ios::hex | ios::uppercase); //通过flag函数一步到位，等同于unsetf+setf
    cout.setf(ios::showbase);
    cout << number << endl;
    cout << count << endl;
}

//链式调用。根据重载的操作符<<去调用相关的函数，由于重载的<<返回的是标准输出的对象引用，所以可以达成链式调用的目的
static inline void test02() {
    using namespace std;
    int num = 10;
    cout
            << setiosflags(ios::showbase | ios::uppercase)
            << hex
            << num
            << endl;
}

//标准输出设置输出格式
// int main() {
//     // test01();
//     test02();
//     return 0;
// }
