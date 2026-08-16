//
// Created by Administrator on 2026/7/9.
//
#include <iostream>
using namespace std;

//通过传递数组的引用在函数内进行操作
//这里需要注意，形参作为引用传递时，必须指明数组的大小，保持参数一致
void foreach(int (&arr)[5]) {
    int size = sizeof(arr) / sizeof(int);
    cout << size << endl;
}

// int main() {
//     int arr[]{1, 2, 3, 4, 5};
//     int size = 5, size1 = 20, size2 = 30;
//     foreach(arr);
//
//     //指针数组
//     int *arr2[10];
//     //数组指针，指向数组的一个指针
//     int (*arr3)[5] = &arr;
//     //声明返回值为数组指针的函数
//     int (*func(int))[5];
//     //这种声明函数方式等价于上面
//     typedef int arrs[5];
//     arrs * funcs(int);
//
//     //c++11新增的尾置返回类型
//     auto funcs1(int) -> int (*)[5];
//
//     return 0;
// }
