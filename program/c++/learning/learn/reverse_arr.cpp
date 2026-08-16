//
// Created by Administrator on 2026/7/8.
//

#include <iostream>

void reverse_arr(int arr[], int &size) {
    for (int i = 0; i <= size / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = tmp;
    }
}

// int main() {
//     int arr[]{1, 2, 3, 4, 5, 6, 7, 8}, size = sizeof(arr) / sizeof(int);
//     reverse_arr(arr, size);
//     for (int i=0;i<size;i++) {
//         std::cout << arr[i] << std::endl;
//     }
//     return 0;
// }
