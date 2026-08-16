//
// Created by Administrator on 2026/7/9.
//
#include <iostream>
using namespace std;

int search(const int (&arr)[7], int start, int end, int target) {
    if (start > end || arr[start] > target || arr[end] < target)
        return -1;
    int mid = start + ((end - start) >> 1);
    int num = arr[mid];
    if (num == target)
        return mid;
    if (num < target)
        return search(arr, mid + 1, end, target);
    return search(arr, start, mid - 1, target);
}

// int main() {
//     int arr[]{1, 2, 3, 4, 5, 6, 7}, size = sizeof(arr) / sizeof(int);
//     cout << search(arr, 0, size - 1, 8) << endl;
//     return 0;
// }
