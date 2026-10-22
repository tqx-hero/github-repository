//
// Created by 田庆新 on 2026/9/2.
//
/**
* 24. 两两交换链表中的节点
已解答
中等
相关标签
premium lock icon
相关企业
给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。



示例 1：


输入：head = [1,2,3,4]
输出：[2,1,4,3]
示例 2：

输入：head = []
输出：[]
示例 3：

输入：head = [1]
输出：[1]


提示：

链表中节点的数目在范围 [0, 100] 内
0 <= Node.val <= 100
 * @return
 */
#include "../../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        if (!head || !head->next)
            return head;
        ListNode dummy(0, head);
        ListNode *prev = &dummy, *cur = prev->next->next;
        while (cur) {
            ListNode *prev_next = prev->next, *cur_next = cur->next;
            prev->next = cur;
            cur->next = prev_next;
            prev_next->next = cur_next;
            //指针都前移2个单位
            prev = prev->next->next;
            cur = prev->next;
            if (cur)
                cur = cur->next;
        }
        return dummy.next;
    }
};

// int main() {
//     ListNode l4(4);
//     ListNode l3(3, &l4);
//     ListNode l2(2, &l3);
//     ListNode l1(1, &l2);
//     Solution sl;
//     ListNode *list_node = sl.swapPairs(&l1);
//     while (list_node) {
//         cout << list_node->val << endl;
//         list_node = list_node->next;
//     }
//     return 0;
// }
