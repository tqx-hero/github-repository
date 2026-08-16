//
// Created by Administrator on 2026/7/9.
//
#include <iostream>
using namespace std;

int jie_cheng(int x) {
    if (x <= 1)
        return 1;
    return x * jie_cheng(x - 1);
}

// int main() {
//     int n = 5;
//     cout << jie_cheng(n) << endl;
//     return 0;
// }
