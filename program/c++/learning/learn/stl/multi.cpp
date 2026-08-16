//
// Created by Administrator on 2026/7/19.
//

#include <iostream>
#include <map>
#include <string>

// int main() {
//     std::multimap<int, std::string> cache;
//     cache.emplace(1, "登录1");
//     cache.emplace(1, "登录2");
//     cache.emplace(1, "登录3");
//     _STD cout << cache.count(1) << _STD endl;
//
//     //第一种遍历方式，直接使用equal_range，获取符合key的左右区间，左闭右开
//     //equal_range查询出等于key的迭代器begin、end
//     // auto range = cache.equal_range(2);
//     // auto &begin = range.first, &end = range.second;
//     // while (begin != end) {
//     //     _STD cout << begin->second << _STD endl;
//     //     ++begin;
//     // }
//     //第二种遍历方式,先查询count，大于0，再找到符合条件的迭代器起始位置，根据count进行自增遍历
//     //但是这样会多查一次树，先count再查范围,性能不如上述的方式
//     int cnt = 0;
//     if ((cnt = cache.count(1))) {
//         auto bound = cache.lower_bound(1);
//         for (int i = 0; i < cnt; i++, ++bound) {
//             _STD cout << bound->second << _STD endl;
//         }
//     }
//
//     return 0;
// }
