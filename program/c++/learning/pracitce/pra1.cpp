#include <random>
#include <vector>
//
// Created by Administrator on 2026/7/20.
//
#include <iostream>
#define _ENDLINE \
    _STD cout << _STD endl

namespace practice {
    template<typename T>
    struct MyPrint {
        void operator()(const T &x) const {
            _STD cout << x << " ";
        }
    };

    template<class T>
    struct MySort {
        bool operator()(const T &x, const T &y) const {
            return x <= y;
        }

        [[nodiscard]] bool greater(const T &x, const T &y) const {
            return x >= y;
        }
    };
}
//声明的外部常量必须在声明时使用extern使其具有外部链接属性，否则默认是内部连接属性(作用域与static相同)
//外部声明无法链接
extern const int const_number;

// int main() {
//     using namespace std;
//     using namespace practice;
//     vector<int> intList;
//     //生成随机数
//     mt19937 rng(random_device{}());
//     uniform_int_distribution<> dist(0, 100);
//     for (int i = 0; i < 10; i++) {
//         intList.push_back(dist(rng));
//     }
//     //遍历
//     ranges::for_each(intList, MyPrint<int>());
//     _ENDLINE;
//     ranges::sort(intList, MySort<int>());
//     ranges::for_each(intList, MyPrint<int>());
//     _ENDLINE;
//     ranges::sort(intList, [](const int &x, const int &y) { return MySort<int>().greater(x, y); });
//     ranges::for_each(intList, MyPrint<int>());
//     _ENDLINE;
//     ranges::reverse(intList);
//     ranges::for_each(intList, MyPrint<int>());
//     _ENDLINE;
//
//     _STD cout << const_number << _STD endl;
//     return 0;
// }
