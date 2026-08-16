//
// Created by Administrator on 2026/7/20.
//
#include "average.h"
namespace average {
    double average(const int &x, const int& y) {
        return (x + y) / 2.0;
    };
}

double global_average(const int &x, const int& y) {
    return (x + y) / 2.0;
}