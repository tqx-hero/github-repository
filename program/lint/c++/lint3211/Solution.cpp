//
// Created by Administrator on 2026/7/7.
//
/**
* 3211 · 队列预发布
C++
入门
通过率
68%

题目
题解29
笔记
讨论1
排名
记录
该题目为预发布题目，如遇到任何问题，请及时通过"题目纠错"联系我们，我们会升级您的账号为VIP作为感谢。
描述
现给你一个储存整形元素的队列 queue<int>，请你返回队列中的 第三个 元素。
如果队列中的元素个数不到 3 个，则返回 -1。

本题需要你补全文件 Solution.cpp 文件中的函数 getQueue3 中的代码。
评测机会运行 main.cpp 通过导入自定义函数库的方式调用 Soluction.cpp 中的 getQueue3 函数，并获取你的返回值来判断结果的正确性。

元素个数不超过
1
0
8
10
8
  个。

使用 <queue> 库中堆栈容器来解决问题。
样例
输入样例 1：

[1,2,3,4]
输出样例 1：

3
按照给定的队列顺序，第一个元素为 1，第二个元素为 2，第三个元素为 3。

输入样例 2：

[1,2]
输出样例 2：

-1
由于队列中的元素少于 3 个，因此返回 -1。
 * @return
 */
#include <queue>
#include <iostream>
using namespace std;

int getQueue3(queue<int> &q) {
    if (q.size() < 3)
        return -1;
    q.pop();
    q.pop();
    return q.front();
}

int main() {
    queue<int> que;
    que.push(1);
    que.push(2);
    // que.push(3);
    // que.push(4);
    cout << getQueue3(que) <<endl;
    return 0;
}
