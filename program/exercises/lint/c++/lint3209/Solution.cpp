//
// Created by Administrator on 2026/7/7.
//
/**
* 3209 · 搬果子预发布
C++
中等
通过率
59%

题目
题解52
笔记
讨论
排名
记录
该题目为预发布题目，如遇到任何问题，请及时通过"题目纠错"联系我们，我们会升级您的账号为VIP作为感谢。
描述
小明来果园里摘果子，摘完了，果子零散的分成了几堆。
现在小明想把这些果子合成一堆，请你设计一个算法使得小明搬果子消耗的体力最少。

注意：

搬运 1 个果子需要消耗 1 点体力。
每次只能把两堆果子合并到一起。
例：
如要搬运 1 3 8 这 3 堆果子，最省力的方式是：

先把 1 3 搬到一起，消耗 4 点体力，现在果子变成了 4 8 这两堆。
再把 4 8 搬到一起，消耗 12 点体力，现在果子只有 12 这一堆了。
总共消耗了 4 + 12 这 16 点体力。
此函数：

接收一个储存整形数据的向量容器 fruits 表示几堆果子依次有多少个。
返回一个 int 型的整数，表示搬运这几堆果子到一起总共需要消耗多少体力。
本题需要你补全文件 Solution.cpp 文件中的函数 carry 中的代码。
评测机会运行 main.cpp 通过导入自定义函数库的方式调用 Soluction.cpp 中的 carry 函数，并获取你的返回值来判断结果的正确性。

题目保证，给定数据最后消耗的体力值在 int 的数据范围内。

使用 <set> 库中集合容器自动排序的特性来解决问题。
数据和合并过程中都有可能出现重复元素。
样例
输入样例 1：

[2,2,3,3,6]
输出样例 1：

36
最省力的搬运方式是：
2 + 2 = 4 -> 4,3,3,6
3 + 3 = 6 -> 4,6,6
4 + 6 = 10 -> 10,6
6 + 10 = 16 -> 16
4 + 6 + 10 + 16 = 36

输入样例 2：

[]
输出样例 2：

0
没有果子需要搬运，所以消耗体力为 0。
 * @return
 */
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

int carry(vector<int> &fruits) {
    int ans = 0;
    priority_queue<int, vector<int>, greater<int> > minHeap(fruits.begin(), fruits.end());
    while (minHeap.size() >= 2) {
        int t1 = minHeap.top();
        minHeap.pop();
        int tot = minHeap.top() + t1;
        minHeap.pop();
        ans += tot;
        minHeap.push(tot);
    }
    return ans;
}

int main() {
    //[2,2,3,3,6]
    vector<int> fruits{2, 2, 3, 3, 6};
    int lost = carry(fruits);
    cout << lost << endl;
    return 0;
}
