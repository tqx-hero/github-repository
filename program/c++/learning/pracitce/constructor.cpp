//
// Created by Administrator on 2026/7/21.
//
#include <iostream>
namespace constr {
    using namespace std;
    class Ts {
    public:
        Ts():num(10),count(0) {
            cout << "无参构造" << endl;
        }

        Ts(int num,const int c) : num(num),count(c) {
            cout << "有参构造" << endl;
        }

    private:
        //可以对成员变量设置默认值，等同于无参构造的初始化列表设置默认值
        int num = 100;
        //对于const成员变量或者引用类型，必须在构造函数的初始化列表中设置它的值
        //不能在函数体内部进行赋值。
        //因为const变量与引用都是顶层const类型，必须在初始化时就要对其进行默认值设置
        //后续只读，而在函数体内部已经属于赋值操作了，但是常量是不可变的，只能在初始化时进行赋值，且只能赋值一次
        const int count = 200;
    };
}

// int main() {
//     //构造函数中，有参构造有默认值，所以有参构造可以无参数
//     //当无参数时与第一个无参构造产生歧义
//     constr::Ts t,tss(1000,3000);
//
//     return 0;
// }
