//
// Created by Administrator on 2026/8/6.
//


#include <iostream>

/**
 * 判断当前系统的字节序是大端还是小端
 * @return
 */
int main() {
    int test = 97;
    char * ch = reinterpret_cast<char*>(&test);
    std::cout << *ch << std::endl;
    return 0;
}
