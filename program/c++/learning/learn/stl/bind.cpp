//
// Created by Administrator on 2026/7/19.
//
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <random>

namespace my_func {
    struct MPrint {
        auto operator()(const int x) const {
            std::cout << x << " ";
        }

        void operator()(const int x, const int y) const {
            std::cout << x + y << " ";
        }
    };

    struct MySort {
        auto operator()(const int &t1, const int &t2) const -> decltype(t2 == t1) {
            return t1 >= t2;
        }
    };

    struct MyMatch {
        auto operator()(const int &x, const int &y) const -> decltype(x == y) {
            return x > y;
        }
    };
}

// int main() {
//     using namespace std;
//     using namespace my_func;
//     std::vector<int> list;
//     mt19937 rng(random_device{}());
//     uniform_int_distribution<int> dist(1, 100);
//     for (int i = 0; i < 10; i++)
//         list.push_back(dist(rng));
//
//     // std::ranges::for_each(list, [](int x) { MPrint()(x, 10); });
//     //
//     // cout << "-------------------------" << endl;
//     // //底层原理就是当要调用的函数所需要的参数与实际传参不匹配时
//     // //使用bind类进行封装，将要调用的类的成员函数，实体对象、参数列表等全部包装生成bind对象返回回来
//     // //当函数比如算法库中foreach，调用第三个参数，函数时，实际上是调用的bind封装的仿函数
//     // //仿函数之前存储了目标函数所需要的信息，包括地址、参数列表，调用对象等，所以调用bind仿函数时，该仿函数就会去调用
//     // //目标对象，返回结果，往上返回，达到适配器的目的。
//     // const auto &binder = [](int x) { MPrint()(30, x); };
//     // //placeholders为占位符，设置后面动态传入参数的位置
//     // binder(100);
//     ranges::for_each(list, [](int x) { MPrint()(0, x); });
//     cout << endl;
//     //lambda表达式使用，非常舒服,取反直接!
//     // ranges::sort(list, [](int x, int y) { return !MySort()(x, y); });
//     // ranges::sort(list, [](int x, int y) { return MySort()(x, y); });
//     // ranges::for_each(list, MPrint());
//     // cout << endl;
//
//     //find_if函数
//     // const auto &iter =
//     // ranges::find_if(list, [](int x) { return MyMatch()(x, 10); });
//     // for_each(iter, list.end(), MPrint());
//
//     //升序排列
//     ranges::sort(list, ranges::less());
//     ranges::for_each(list, MPrint());
//     cout << endl;
//     //逆序排列
//     ranges::sort(list, ranges::greater{});
//     ranges::for_each(list, MPrint());
//     cout << endl;
//     return 0;
// }
