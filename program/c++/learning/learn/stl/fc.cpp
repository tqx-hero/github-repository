//
// Created by Administrator on 2026/7/19.
//
#include <iostream>
#include <algorithm>
#include <vector>

namespace fc {
    template<typename T>
    struct MyFunc {
        MyFunc() : count(0) {
        };

        explicit MyFunc(int num)
            : count(0), num(num) {
        }

        int count;
        int num;

        void operator()(const T &t1) {
            count++;
            _STD cout << t1 << _STD endl;
        }

        void operator()(const MyFunc &fc) {
            (*this)(fc.num);
        }
    };
}

// int main() {
//     using MyFuncType = fc::MyFunc<int>;
//     MyFuncType func;
//     // func(20);
//     // func(30);
//     // func(40);
//     // func(10);
//     // _STD cout << func.count << _STD endl;
//
//     _STD vector<MyFuncType> list{MyFuncType(10), MyFuncType(20), MyFuncType(5), MyFuncType(1)};
//
//     // MyFuncType &funcRef = func;
//     //foreach接收的_Fn类型，由于没有带引用标识符，所以传入的参数不管是引用还是对象，都会再函数内部解读成值传递，进行一次拷贝
//     //但指针不会，指针可以保留类型
//     // MyFuncType fcTemp = _STD for_each(list.begin(), list.end(), funcRef);
//
//     //通过ranges::for_each仿函数去进行遍历。这样可以直接传递容器，函数内部进行自动获取迭代器的begin、end，进行遍历
//     auto result = _STD ranges::for_each(list, func);
//     //2个对象不一样，foreach返回接收的都是对象的拷贝副本，没有接收引用，所以返回时会对其进行拷贝构造，前后的对象不是同一个
//     // _STD cout << (fcTemp.count == func.count) << _STD endl;
//     // _STD cout << fcTemp.count << _STD endl;
//     // _STD cout << funcRef.count << _STD endl;
//     return 0;
// }
