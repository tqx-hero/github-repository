//
// Created by Administrator on 2026/7/22.
//
#include <iostream>

// int main() {
//     using namespace std;
//     // int *ia = new int;
//     // double *dd = nullptr;
//     // try {
//     //     dd = new double[20];
//     //     throw bad_alloc();
//     // } catch (bad_alloc &e) {
//     //     cout << "出现异常 : " << e.what() << endl;
//     // }
//     // cout << "---------------------" << endl;
//     // delete ia;
//     // delete[] dd;
//     //设置new操作符申请内存失败的行为
//     //默认失败会抛出bad_alloc异常，并终止程序
//     //使用new(nothrow) 方式，可以让它不抛异常，返回空指针，行为与c标准相同
//     int *ap = new(nothrow) int;
//     if (!ap) {
//         cout << "空指针，申请内存失败" << endl;
//     }
//
//     return 0;
// }
