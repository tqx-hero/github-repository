//
// Created by Administrator on 2026/7/5.
//

#ifndef C___NODE_H
#define C___NODE_H


/**
* 3760 · 简单实现链表的插入与删除
C++
简单
通过率
63%
￼
￼
￼
题目
题解
13
笔记
讨论
排名
记录
描述
现有一个链表类 Node，已经为你写好了它的构造函数 Node() 和 Node(value)，无需对它们进行修改。
你需要做的是实现链表的 插入 与 删除，分别对应以下两个方法：
• insert(Node* head, int index, int val)：在以 head 为头节点的链表的 index 位置处，插入一个值为 value 的新节点
• remove(Node* head, int index)：删除以 head 为头节点的链表的 index 位置处的节点
需要注意的是，链表的下标是 从 0 开始，如链表 node = 1->2->3->4 中，index = 2 的节点值为 3。
￼
1
≤
𝑖
𝑛
𝑠
𝑒
𝑟
𝑡
_
𝑖
𝑛
𝑑
𝑒
𝑥
≤
𝑛
𝑜
𝑑
𝑒
.
𝑙
𝑒
𝑛
𝑔
𝑡
ℎ
1
≤
𝑟
𝑒
𝑚
𝑜
𝑣
𝑒
_
𝑖
𝑛
𝑑
𝑒
𝑥
<
𝑛
𝑜
𝑑
𝑒
.
𝑙
𝑒
𝑛
𝑔
𝑡
ℎ
样例
输入数据由 两行 整数组成，其中：
• 第一行表示 构成链表的整数集，每个整数由空格 ' ' 分隔
• 第二行由 三个整数 组成，分别代表 插入的位置 insert_index、插入的节点值 insert_value 和 删除的位置 remove_index
样例一
输入
1 2 3 5 6
3 4 5
输出
1 2 3 4 5 6
1 2 3 4 5
样例二
输入
1
1 2 1
输出
1 2
1
相关知识
 */
class Node {
public:
    int value;
    Node *next;

    explicit Node() {
        value = 0;
        next = nullptr;
    }

    explicit Node(int value) : value(value) {
        next = nullptr;
    }

    static void insert(Node *head, int index, int val) {
        Node *node = new Node(val);
        int idx = 0;
        Node *cur = head;
        while (idx++ < index - 1)
            cur = cur->next;
        node->next = cur->next;
        cur->next = node;
    }

    static void remove(Node *head, int index) {
        Node *cur = head;
        int idx = 0;
        while (idx++ < index - 1)
            cur = cur->next;
        Node *node = cur->next;
        cur->next = node ? node->next : nullptr;
        delete node;
        node = nullptr;
    }
};


#endif //C___NODE_H
