//
// Created by Administrator on 2026/8/12.
//
/**
* 反转链表
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。 
示例 1：
输入：
head = [1,2,3,4,5]
输出：
[5,4,3,2,1]
示例 2：
输入：
head = [1,2]
输出：
[2,1]
示例 3：
输入：
head = []
输出：
[]
  提示：
• 链表中节点的数目范围是 [0, 5000]
• -5000 <= Node.val <= 5000 
进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？
 * @return
 */
#include "../../../link/ListNode.h"

class Solution {
    ListNode *prev = nullptr;

    void loopReverse(ListNode *head) {
        if (!head)
            return;
        auto next_node = head->next;
        head->next = prev;
        prev = head;
        loopReverse(next_node);
    }

public:
    //迭代实现
    // ListNode *reverseList(ListNode *head) {
    //     if (!head || !head->next)
    //         return head;
    //     ListNode *cur = head, *prev = nullptr;
    //     while (cur) {
    //         auto next = cur->next;
    //         cur->next = prev;
    //         prev = cur;
    //         cur = next;
    //     }
    //     return prev;
    // }
    //递归实现
    ListNode *reverseList(ListNode *head) {
        if (!head)
            return head;
        loopReverse(head);
        return prev;
    }
};

// int main() {
//     return 0;
// }
