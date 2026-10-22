//
// Created by Administrator on 2026/7/7.
//

/**
* 3212 · 有这个学生吗？预发布
C++
入门
通过率
64%

题目
题解31
笔记
讨论3
排名
记录
该题目为预发布题目，如遇到任何问题，请及时通过"题目纠错"联系我们，我们会升级您的账号为VIP作为感谢。
描述
给你一个储存 学生 id：学生姓名 的字典 map<int, string> stu_info；和一个要查询的 学生 id stu_id。
请你从信息表中查询 学生 id 对应的学生姓名并返回，如果找不到就返回 no this man。

本题需要你补全文件 Solution.cpp 文件中的函数 getStuName 中的代码。
评测机会运行 main.cpp 通过导入自定义函数库的方式调用 Solution.cpp 中的 getStuName 函数，并获取你的返回值来判断结果的正确性。

学生个数不超过
5
∗
1
0
7
5∗10
7
  个。

样例
输入样例 1：

[1:"Jack",2:"James",3:"Blue",4:"Sunny"]
3
输出样例 1：

Blue
学号 3 在字典中，对应的学生姓名为 "Blue"。

输入样例 2：

[1:"Jack",2:"James",3:"Blue",4:"Sunny"]
6
输出样例 2：

no this man
学号 6 不在字典中，因此返回 "no this man"。
 * @return
 */
#include <string>
#include <iostream>
#include <map>
using namespace std;

string getStuName(map<int, string> &stu_info, int stu_id) {
    // write your code here
    string ans;
    auto pair = stu_info.find(stu_id);
    if (pair == stu_info.end())
        ans = "no this man";
    else
        ans = pair->second;
    return ans;
}

int main() {
    //1:"Jack",2:"James",3:"Blue",4:"Sunny"
    map<int, string> map{{1, "Jack"}, {2, "James"}, {3, "Blue"}, {4, "Sunny"}};
    cout << getStuName(map, 5) << endl;
    return 0;
}
