//
// Created by Administrator on 2026/7/23.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//可变参数与参数的收集
void collector(vector<int> &list) {
}

template<typename T, typename... Args>
void collector(vector<int> &list, T &data, const Args &... args) {
    list.push_back(data);
    collector(list, args...);
}

// int main() {
//     int a = 1, b = 2, c = 3, d = 4;
//     vector<int> list;
//     collector(list, a, b, c, d);
//     std::ranges::for_each(list, [](const int &a) { std::cout << a << " "; });
//     return 0;
// }
