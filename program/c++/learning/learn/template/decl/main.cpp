//
// Created by Administrator on 2026/7/18.
//
#include <iostream>

//使用函数模板时，通过decltype类型推导来自动推导函数返回值类型
//使用新c++11之后的后置返回值类型语法
template<typename T, typename K>
auto funcn(const T &t1, const K &t2) -> decltype(t1 + t2) {
    return t1 + t2;
}

//自动推断带(),返回的是括号内类型的引用
template<typename T, typename K>
auto funcRef(T &t1, const K &t2) -> decltype((t1) ) {
    return t1 += t2;
}

// int main() {
//     using namespace std;
//     // int num = 10;
//     // //自动推导类型，如果带(),类型则为结果类型的引用
//     // decltype((num)) m = num;
//     // m = 20;
//     // cout << num << endl;
//
//     // double fl=2.8f;
//     // int i = 100;
//     // //自动类型推导
//     // decltype(fl+i) res = i+fl;
//     // cout << sizeof(res) << endl;
//     // cout << res << endl;
//
//     // short st = 100;
//     // long long ll = 300L;
//     // long long ret = funcn(st, ll);
//     // cout << ret << endl;
//     // cout << sizeof(ret) << endl;
//
//     int in = 100;
//     char ch = 10;
//     int &ref = funcRef(in, ch);
//     cout << ref << endl;
//     cout << in << endl;
//     return 0;
// }
