//
// Created by Administrator on 2026/7/19.
//
#include <iostream>
#include <random>
#include <vector>

namespace my_sort {
    void print(const int &x) {
        _STD cout << x << " ";
    }

    struct Print {
        void print(const int &x) const {
            _STD cout << x << " ";
        }
    };
}

// int main() {
//     using namespace std;
//     vector<int> list;
//     mt19937 rng(random_device{}());
//     uniform_int_distribution<int> dist(10, 100);
//     for (int i = 0; i < 10; i++)
//         list.push_back(dist(rng));
//     //通过直接调用函数方式
//     // ranges::for_each(list, [](int x) { my_sort::print(x); });
//     my_sort::Print p;
//     ranges::for_each(list, [&p](int x)-> void { p.print(x); });
//     return 0;
// }
