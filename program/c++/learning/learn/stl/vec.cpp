//
// Created by Administrator on 2026/7/18.
//
#include <vector>
#include <iostream>

namespace stl_vec {
    template<typename T>
    void printVec(std::vector<T> &list) {
        for (auto i: list)
            std::cout << i << " ";
        std::cout << std::endl;
    }
}

// int main() {
//     using namespace std;
//     using namespace stl_vec;
//     int arr[]{10, 20, 30, 5, 6, 7, 3, 1};
//     //用数组初始化vector
//     vector<int> v1(arr, reinterpret_cast<int *>(&arr + 1));
//     printVec(v1);
//     //调用vector的拷贝构造，生成v2对象
//     decltype(v1) v2(v1);
//     cout << v2.capacity() << endl;
//     cout << v2.size() << endl;
//
//     //调用构造函数，传入了2个指针(迭代器)来初始化v3
//     decltype(v1) v3(v2.begin(), v2.end());
//     int cn = 100;
//     for (int &i: v3)
//         i = cn++;
//     printVec(v3);
//     //交换2个vector，实质是交换了底层维护的数组指针，2个指针互相交换，包括一些属性等，无数组的拷贝开销
//     v3.swap(v2);
//     printVec(v3);
//     // using my_vector = vector<int> ;
//     // my_vector v4(v3);
//     return 0;
// }
