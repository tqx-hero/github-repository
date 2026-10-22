//
// Created by Administrator on 2026/7/5.
//

#ifndef C___SOLUTION_H
#define C___SOLUTION_H


/**
* 3759 · 获取链表中指定下标的节点
C++
简单
通过率
80%

题目
题解15
笔记
讨论
排名
记录
描述
现给定一个链表的头结点 head 和一个整数 index 表示下标，链表中的节点下标值从 0 开始。

你需要完成 solution.cpp 中的 getNode() 函数，以实现找到该链表中下标为 index 的节点，并将其返回。

链表类的定义已在 node.cpp 中给出，我们将获取输入数据并对其进行初始化，相关逻辑代码可参考 main.cpp。

0
≤
N
o
d
e
.
v
a
l
u
e
≤
1
0
5
0≤Node.value≤10
5


0
≤
i
n
d
e
x
≤
h
e
a
d
.
l
e
n
g
t
h
0≤index≤head.length

样例
输入数据由 2 行数据组成，第一行表示 链表中每个节点的值，每个值由 空格（' '） 进行分割。第二行表示 需要寻找的下标值。

样例一

输入

1 3 5 7 9
3
输出

7
样例二

输入

1 3 5 7 9
0
输出

1
相关知识
 */
#include "../lint3760/node.h"

class solution {
public:
    static Node *getNode(Node *head, int index);
};


#endif //C___SOLUTION_H
