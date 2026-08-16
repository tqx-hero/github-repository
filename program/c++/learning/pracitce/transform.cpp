//
// Created by Administrator on 2026/7/20.
//
#include <iostream>

void show(short s1, short s2) {
    _STD cout << s1 << " , " << s2 << _STD endl;
}


namespace tran {
    class Test {
    public:
        explicit Test(double num, bool flag = false) : num(num), flag(flag) {
            _STD cout << "num : " << this->num << _STD endl;
        }

        //重载操作符int()，即对象Test强转成int类型
        //当int i = test();时触发该重载操作函数
        //如果不加explicit，int i = test()语句有效，但是会出现一些问题，比如有两个重载函数:
        //1、show(int,int)；2、show(Test,Test)
        //我本想调用第二个函数但是没有把它的定义文件导入，反而导入了第一个函数的文件
        //编译器查找函数进行匹配时，没找到完全匹配的类型，会调用该函数进行隐式类型转换，即把Test()对象强转为int，
        //再去调用第一个show函数，这样就出现了非常严重的问题，掉错了函数还很难排查。
        //所以对于强转操作必须声明成explicit，使其显式强转
        explicit operator int() const {
            return static_cast<int>(num);
        }
        //bool()不受explicit影响，即使加了，当使用诸如if(test())判断时，编译器同样会调用该重载函数进行隐式类型转换
        explicit operator bool() const {
            _STD cout << "func bool(test())..." << _STD endl;
            return flag;
        }

    private:
        double num;
        bool flag;
    };
}

// void show(tran::Test s1, tran::Test s2) {
//     _STD cout << "test()..." << _STD endl;
// }


// int main() {
//     //隐式类型转换：编译器会根据参数类型+函数名，匹配要调用的函数。
//     //当发现有匹配的函数，会进行调用。
//     //如果函数名相同，参数类型不同，且没找到完全匹配的函数，编译器会进行隐式类型转换
//     //即找到最匹配的那个函数(类型范围为从大到小，尽量不丢失精度)，把实参类型强转为形参类型
//     //所以下面这个会从int->short，高位全部截断
//     show(100000, 200000);
//
//     using tran::Test;
//     //构造函数添加显式声明后，将不能进行隐式类型转换，即编译器不会自动调用相应的构造函数再去构造该对象
//     //必须显式给出构造器。
//     // Test ts = 10.11f; //error
//     Test tt(10, true);
//     //重载了强转操作符int()后，必须显式进行强转，这样语义更清晰。
//     show(static_cast<int>(tt), static_cast<int>(tt));
//     //bool类型不受explicit约束，可以直接运用重载bool()强转
//     if (tt) {
//         _STD cout << "bool(test())..." << _STD endl;
//     }
//     return 0;
// }
