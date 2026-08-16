//
// Created by Administrator on 2026/7/8.
//
#include <iostream>
using namespace std;

// int main() {
//     int arr[] = {1, 2, 3, 4, 5};
//     //数组指针，指针所在的内存单元中存放的是数组arr的地址，arr的地址即为首元素地址
//     int (*ap)[5] = &arr;
//     //所以解引用后拿到的其实就是数组的地址，数组地址就是数组首元素的地址
//     // int * pa = *ap;
//     // for (int i=0;i<5;i++) {
//     //      cout << pa[i] << endl;
//     // }
//     //强转为不同的指针类型，寻址方式，偏移量的计算都改变了，即解释方式变了，但是内存单元的数据仍不变。
//     // long long *lp = (long long *) *ap;
//     // for (int i = 0; i < 3; i++) {
//     //     cout << lp[i] << endl;
//     // }
//     int arr2[] = {6, 7, 8, 9, 10};
//     //指针数组，存放的每一个元素都是一个指针
//     int *arrp[] = {arr, arr2};
//     for (int i = 0; i < 2; i++) {
//         int *an = *(arrp + i);
//         for (int j = 0; j < 5; j++) {
//             cout << an[j] << endl;
//         }
//     }
//
//     return 0;
// }
