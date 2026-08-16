//
// Created by Administrator on 2026/7/5.
//

#ifndef C___NODE_H
#define C___NODE_H


/**
* 3758 · 创建简单链表类
C++
简单
通过率
65%

题目
题解9
笔记
讨论1
排名
记录
描述
在本题中，你需要实现一个简单的 链表 类，它需要包含 2 个成员变量，分别表示 节点值 和 指向下一个节点。

另外，你还需要定义它的构造函数，使得传入一个 整数 后能够构造某一个节点。比如，当需要构造一个值为 10 的节点时：

Node node(10);
需要执行以下操作：

初始化值为 10 的节点
输出 Init a new node with value 10
请完成 node.cpp 文件的编写，我们将在 Main.cpp 中使用类似上述的代码进行节点初始化。

样例
样例一

输入

10
输出

Init a new node with value 10
样例二

输入

10 20
输出

Init a new node with value 10
Init a new node with value 20
推荐课程
 */
#include <iostream>
using namespace std;

class Node {
    int value;
    Node *next;

public:
    Node(int value);

    virtual ~Node();
};


#endif //C___NODE_H
