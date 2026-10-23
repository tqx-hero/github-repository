//
// Created by Administrator on 2026/7/24.
//
/**
* LCR 028. 扁平化多级双向链表
中等
相关标签
premium lock icon
相关企业
多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，可能指向单独的双向链表。这些子列表也可能会有一个或多个自己的子项，依此类推，生成多级数据结构，如下面的示例所示。

给定位于列表第一级的头节点，请扁平化列表，即将这样的多级双向链表展平成普通的双向链表，使所有结点出现在单级双链表中。



示例 1：

输入：head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
输出：[1,2,3,7,8,11,12,9,10,4,5,6]
解释：

输入的多级列表如下图所示：



扁平化后的链表如下图：


示例 2：

输入：head = [1,2,null,3]
输出：[1,3,2]
解释：

输入的多级列表如下图所示：

  1---2---NULL
  |
  3---NULL
示例 3：

输入：head = []
输出：[]


如何表示测试用例中的多级链表？

以 示例 1 为例：

 1---2---3---4---5---6--NULL
         |
         7---8---9---10--NULL
             |
             11--12--NULL
序列化其中的每一级之后：

[1,2,3,4,5,6,null]
[7,8,9,10,null]
[11,12,null]
为了将每一级都序列化到一起，我们需要每一级中添加值为 null 的元素，以表示没有节点连接到上一级的上级节点。

[1,2,3,4,5,6,null]
[null,null,7,8,9,10,null]
[null,11,12,null]
合并所有序列化结果，并去除末尾的 null 。

[1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]


提示：

节点数目不超过 1000
1 <= Node.val <= 10^5

 * @return
 */

#include <iostream>

class Node {
public:
    int val;
    Node *prev;
    Node *next;
    Node *child;

    Node() = default;

    Node(int val, Node *next, Node *child)
        : val(val),
          prev(nullptr),
          next(next),
          child(child) {
    }

    Node(int val, Node *prev, Node *next, Node *child)
        : val(val),
          prev(prev),
          next(next),
          child(child) {
    }
};

class Solution {
public:
    Node *flatten(Node *head) {
        Node dummy;
        Node *dptr = &dummy;
        flattenNode(head, dptr);
        auto ret = dummy.next;
        if (ret)
            ret->prev = nullptr;
        return ret;
    }

private:
    void flattenNode(Node *head, Node *&dummy) {
        if (!head)
            return;
        dummy->next = head;
        head->prev = dummy;
        dummy = dummy->next;
        Node *nxt = head->next;
        flattenNode(head->child, dummy);
        head->child = nullptr;
        flattenNode(nxt, dummy);
    }
};

// int main() {
//     /*
//      *输入：
// head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
// 输出：
//         [1,2,3,7,8,11,12,9,10,4,5,6]*/
//     Node n12(12, nullptr, nullptr);
//     Node n11(11, &n12, nullptr);
//     Node n10(10, nullptr, nullptr);
//     Node n9(9, &n10, nullptr);
//     Node n8(8, &n9, &n11);
//     Node n7(7, &n8, nullptr);
//     Node n6(6, nullptr, nullptr);
//     Node n5(5, &n6, nullptr);
//     Node n4(4, &n5, nullptr);
//     Node n3(3, &n4, &n7);
//     Node n2(2, &n3, nullptr);
//     Node n1(1, &n2, nullptr);
//
//     n2.prev = &n1;
//     n3.prev = &n2;
//     n4.prev = &n3;
//     n5.prev = &n4;
//     n6.prev = &n5;
//     n8.prev = &n7;
//     n9.prev = &n8;
//     n10.prev = &n9;
//     n12.prev = &n11;
//
//     Solution sl;
//
//     auto node = sl.flatten(&n1);
//     while (node) {
//         std::cout << node->val << std::endl;
//         node = node->next;
//     }
//     return 0;
// }
