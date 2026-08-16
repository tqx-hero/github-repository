//
// Created by Administrator on 2026/7/7.
//
/**
* 3210 · 火车出入站预发布
C++
中等
通过率
48%

题目
题解43
笔记
讨论1
排名
记录
该题目为预发布题目，如遇到任何问题，请及时通过"题目纠错"联系我们，我们会升级您的账号为VIP作为感谢。
描述
现在有一个车站，只有一个入口，火车只能从唯一的一个出站或者进站。

现在给定你一个火车的进站顺序 in_order，和一个出站顺序 leave_order。

请你设计一个程序来判断火车按照进站顺序进站，能否按照出站顺序出站。

注意：

若 in_order = [1,2,3] 火车 1 进站之前，火车 2 和火车 3 不能入站。
若 leave_order = [1,2,3] 火车 1 出站之前，火车 2 和火车 3 不能出站。
而且如果车站里火车 1 前面还有车，火车 1 也不能出站，因为车站只有一个进出口。
本题需要你补全文件 Solution.cpp 文件中的函数 train 中的代码。

此函数：

接收两个储存整形数据的向量容器 in_order 和 leave_order 表示火车的进站顺序和出站顺序。其中的数据表示火车的编号。
返回一个 bool 型的数据 true or false，表示 火车能按照 leave_order 的顺序出站 或者 不能按照 leave_order 的顺序出站。
评测机会运行 main.cpp 通过导入自定义函数库的方式调用 Soluction.cpp 中的 train 函数，并获取你的返回值来判断结果的正确性。

in_order 和 leave_order 里面的元素个数相同。
没有重复元素。

使用 <stack> 库中堆栈容器来解决问题。
样例
输入样例 1：

[1,2,3]
[1,3,2]
输出样例 1：

true
解释：

火车的运行流程如下：
`1` 入站
`1` 出站
`2` 入站
`3` 入站
`3` 出站
`2` 出站
可以看到 `1` 入站后可以立即出站，`2` 入站后先等着，`3` 入站后再进行出站。
这样入站顺序为 `1,2,3` 时，出站顺序 `1,3,2` 就能够实现。
输入样例 2：

[1,2,3]
[3,1,2]
输出样例 2：

false
解释：

如果想要 `3` 先出站，那么按照入站顺序，就需要先将火车 `1,2` 都入站。
之后 `3` 可以出站。
但是接下来 `1` 想出站，`1` 却被前面的 `2` 挡着，所以这个出站顺序不能实现。
相关知识
 * @return
 */
#include "Tools.cpp"
#include "Solution.cpp"

vector<int> deal(string in_data) {
    replaceByFind(in_data, " \r\n\t");
    if (in_data[0] != '[' || in_data[in_data.size() - 1] != ']') {
        cout << "Your data is [" << in_data << "]." << endl;
        cout << "The square brackets at both ends of the input data are abnormal." << endl;
        return {-11414};
    }
    in_data = in_data.substr(1, in_data.size() - 2);
    vector<int> res;
    for (string n: splitByFind(in_data, ',')) {
        if (n == "") continue;
        try {
            res.push_back(stoi(n));
        } catch (std::invalid_argument msg) {
            cout << "data [" << n << "] error" << endl;
            return {-11414};
        }
    }
    return res;
}

// int main() {
//     string in_data;
//     in_data = "";
//     getline(cin, in_data);
//     vector<int> in_order = deal(in_data);
//     if (in_order.size() && in_order[0] == -11414) return 0;
//     in_data = "";
//     getline(cin, in_data);
//     vector<int> leave_order = deal(in_data);
//     if (leave_order.size() && leave_order[0] == -11414) return 0;
//     cout << (train(in_order, leave_order) ? "true" : "false") << endl;
// END:
//     return 0;
// }
