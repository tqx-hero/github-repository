//
// Created by Administrator on 2026/7/18.
//
#include <set>
#include <iostream>
//set使用api，底层红黑树
// int main() {
//     using namespace std;
//     using SET_INT = set<int>;
//     using Set_iterator = SET_INT::iterator;
//     SET_INT set;
//     set.insert(10);
//     set.insert(20);
//     set.insert(30);
//     set.insert(40);
//     set.insert(33);
//     Set_iterator iter;
//     if ((iter = set.find(20)) != set.end()) //查找某个值存不存在红黑树中
//         cout << *iter << endl;
//     auto it = set.lower_bound(22); //返回大于等于查找值的迭代器
//     //查找第一个严格小于查找值的值
//     if (it != set.begin())
//         cout << *--it << endl;
//     it = set.upper_bound(33); //返回严格大于查找值的迭代器
//     //查找第一个小于等于目标值的值
//     if (it != set.begin())
//         cout << *--it << endl;
//     pair<SET_INT::iterator, SET_INT::iterator> pair = set.equal_range(22); //返回数对<lower_bound,upper_bound>2个迭代器
//     cout << *pair.first << endl;
//     cout << *pair.second << endl;
//     return 0;
// }
