//
// Created by Administrator on 2026/7/15.
//
/**
* 面试题 02.02. 返回倒数第 k 个节点
简单
相关标签
premium lock icon
相关企业
提示
实现一种算法，找出单向链表中倒数第 k 个节点。返回该节点的值。

注意：本题相对原题稍作改动

示例：

输入： 1->2->3->4->5 和 k = 2
输出： 4
说明：

给定的 k 保证是有效的。
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    int kthToLast(ListNode *head, int k) {
        if (!head->next)
            return head->val;
        ListNode *cur = head, *next = cur;
        int i = 0;
        while (i++ < k-1)
            next = next->next;
        while (next->next) {
            cur = cur->next;
            next = next->next;
        }
        return cur->val;
    }
};
//
// int main() {
//     return 0;
// }
