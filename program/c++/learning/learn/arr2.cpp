//
// Created by Administrator on 2026/7/6.
//
#include <iostream>
using namespace std;

void print(const int (&arr)[4][2]);

// int main() {
//     int arr[4][2] = {1, 2, 3, 4, 5, 6, 7, 8};
//     print(arr);
//     return 0;
// }

//二维数组引用形式传参，数组的行列必须固定并显式给出
void print(const int (&arr)[4][2]) {
    //普通的行列遍历形式
    // for (int i = 0; i < std::size(arr); i++) {
    //     for (int j = 0; j < sizeof(arr[0]) / sizeof(int); j++) {
    //         cout << arr[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //c++使用增强for循环，声明每一行元素时必须显式给出其引用的类型，否则编译器会按照指针的方式解读
    for (auto &row: arr) {
        for (auto num: row) {
            cout << num << '\t';
        }
        cout << endl;
    }

    cout << endl;
}
