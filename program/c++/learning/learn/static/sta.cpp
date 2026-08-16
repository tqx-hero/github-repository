//
// Created by Administrator on 2026/7/10.
//
#include <iostream>
using namespace std;

class AC {
    static int p_num;
    int ss;

public:
    static int get_p_num() {
        return p_num;
    }

    static void set(int x) {
        p_num = x;
    }

    //static变量内存开辟在静态变量区，不属于对象，所以不能在类中初始化
    static int num;
    //常量必须在定义时直接进行初始化，因为常量不允许修改，只能初始化时直接进行赋值
    const static int sta_num;
};

//使用必须声明
int AC::num;
const int AC::sta_num = 30;
//私有的static变量也需要先声明，再使用
int AC::p_num = 200;
//静态成员变量不占用类的空间，因为它是在静态区的，不在堆或者栈
// int main() {
//     //在使用之前必须进行赋值
//     AC::num = 20;
//     cout << AC::num << endl;
//
//     // AC a;
//     // a.put(10);
//     // cout << a.get_p_num() << endl;
//     AC::set(30);
//     cout << AC::get_p_num() << endl;
//     cout << sizeof(AC) <<endl;
//     return 0;
// }
