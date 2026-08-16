//
// Created by Administrator on 2026/7/19.
//
#include <vector>
#include <algorithm>
#include <iostream>

struct Tran {
    auto operator()(const int x, const int &y) {
        return x + y;
    }
};

void printTran(const int &x) {
    _STD cout << x << " ";
}

// int main() {
//     using namespace std;
//     vector<int> v1, v2;
//     for (int i = 0; i < 10; i++)
//         v1.push_back(i);
//     //transform之前一定要先给容器设置容量大小，使用resize，不能使用reserve
//     //把v1内的元素拷贝到v2，
//     v2.resize(v1.size());
//     ranges::transform(v1, v2.begin(), [](int x) { return Tran()(x, 10); });
//     ranges::for_each(v2, [](int x) { printTran(x); });
//     return 0;
// }
