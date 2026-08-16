//
// Created by Administrator on 2026/7/18.
//
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
//容器使用算法，传入迭代器的案例，迭代器其实就是两个指针
//即容器的起始地址begin与容器后面的第一个内存地址end。(注意这里的end是不包括在容器内的)
//通过两个指针，函数内部就可以对容器内的数据进行访问，处理，解决相关问题
const int getNumCount(int *begin, int *end, int val) {
    int num = 0;
    while (begin < end) {
        if (*begin == val)
            num++;
        begin++;
    }
    return num;
}

void printArray(int a) {
    std::cout << a << " ";
}

void printVector(const std::string &str) {
    std::cout << str << " ";
}

// int main() {
//     int arr[]{0, 2, 2, 2, 3, 4, 5, 6, 7, 0};
//     // int count = getNumCount(arr, reinterpret_cast<int *>(&arr + 1), 2);
//     // std::cout << count << std::endl;
//     //直接使用指针即可，stl中规定的迭代器类实际上就是指针
//     std::for_each(arr, reinterpret_cast<int *>(&arr + 1), printArray);
//     std::cout << std::endl;
//     std::vector<std::string> str;
//     str.push_back("wang");
//     str.push_back("li");
//     str.push_back("qin");
//     // std::for_each(str.begin(),str.end(),printVector);
//     // std::ranges::for_each(str,printVector); //与上述函数等价，省去了传入迭代器的参数,由stl算法库自动计算迭代器的范围
//     //自己使用迭代器去进行迭代，可以直接在获取迭代器之后把它解引用。
//     //原理是迭代器类的底层重载了与指针相关的运算符
//     //所以可以直接把迭代器当作指针来用
//     for (auto it = str.begin(), ed = str.end(); it < ed; ++it) {
//         std::cout << *it << " ";
//     }
//     return 0;
// }
