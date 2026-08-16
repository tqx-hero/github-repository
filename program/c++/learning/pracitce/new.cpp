//
// Created by Administrator on 2026/7/20.
//
#include <iostream>
#include <new>
char buffer[200];

// int main() {
//     //在buffer空间中申请int[10]大小的空间，返回首元素地址
//     //使用这个地址空间后，实际上是在buffer空间中进行操作
//     int *ptr = new(buffer) int[10];
//     //再次申请long long空间，需要计算buffer的偏移，否则会直接进行覆盖
//     //导致申请的长整型与上面的int类型使用同一块地址
//     long long *ptr1 = new(buffer + 10 * sizeof(int)) long long[5];
//     int cnt = 100;
//     for (int i = 0; i < 10; i++) {
//         ptr[i] = cnt++;
//     }
//
//     for (int i = 0; i < 5; i++) {
//         ptr1[i] = ++cnt + 1000;
//     }
//
//     //可以通过buffer的指针进行访问申请的空间
//     int *bufferPtr = reinterpret_cast<int *>(buffer);
//     for (int i = 0; i < 10; i++) {
//         _STD cout << *bufferPtr++ << " ";
//     }
//
//     long long *bufferLongPtr = reinterpret_cast<long long *>(bufferPtr);
//     for (int i = 0; i < 5; i++) {
//         _STD cout << *bufferLongPtr++ << " ";
//     }
//     return 0;
// }
