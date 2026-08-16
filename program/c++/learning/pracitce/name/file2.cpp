//
// Created by Administrator on 2026/7/20.
//

#include <iostream>
using namespace std;
extern int x;

namespace {
    int y = -4;
}

void another() {
    cout << "another:" << x << ";" << y << endl; //x=10,y=-4
}
