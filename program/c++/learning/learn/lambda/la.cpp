//
// Created by Administrator on 2026/7/23.
//
#include <functional>
#include <iostream>

typedef double (*func)(const int &, const int &);

// int main() {
//     using namespace std;
//     int x = 1021, y = 20;
//
//     //如果lambda表达式带有捕获变量，不能直接用函数指针去接收，可以使用function模板来接收
//     //实质上就是一个仿函数结构体，lambda表达式生成的匿名函数时，会生成一个function对象实例，实例中定义了所捕获的参数列表
//     //作为成员变量，包括形参的参数列表、调用的函数
//     //当使用callable()时，调用的就是这个实例的仿函数，即operator()，它会用传入的this指针，拿到各参数列表以及要调用的真实函数的地址
//     //在进行调用，达到了间接调用的目的.
//     //单纯用函数指针无法携带要捕获的参数列表，所以匿名函数无法用单纯的函数指针去接收，只能用扩展了的function对象去接收
//     function<double()> callable;
//     //lambda表达式用法，就是定义了一个匿名函数，然后去调用即可，如果需要传参，则在函数名[]后面添加()，写入形参列表即可
//     auto ret = [&x,&y] { return static_cast<double>(x) / y; };
//     callable = ret;
//     cout << callable() << endl;
//     // double (*func1)(const int &, const int &) = [](const int &x, const int &y)->double { return static_cast<double>(x) / y; };
//     //对于不带捕获的lambda表达式可以用函数指针接收
//     func fc = [](const int &x, const int &y)-> double { return static_cast<double>(x) / y; };
//     cout << fc(1023, 20) << endl;
//     return 0;
// }
