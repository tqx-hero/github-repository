//
// Created by Administrator on 2026/7/20.
//

#include <iostream>
using namespace std;

void other();

void another();

int x = 10, y;

// int main() {
//     cout << x << endl; //10
//     {
//         int x = 4;
//         cout << x << endl; //4
//         cout << y << endl; //0
//     }
//     other();
//     another();
//     return 0;
// }

void other() {
    int y = 1;
    cout << "other : " << x << ";" << y << endl; //x=10,y =1;
}
