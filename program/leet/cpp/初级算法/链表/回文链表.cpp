//
// Created by Administrator on 2026/8/12.
//
/**
* 回文链表
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。 
示例 1：
输入：
head = [1,2,2,1]
输出：
true
示例 2：
输入：
head = [1,2]
输出：
false
  提示：
• 链表中节点数目在范围[1, 105] 内
• 0 <= Node.val <= 9 
进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 * @return
 */
#include <iostream>

#include "../../../link/ListNode.h"
//将后半段链表翻转，然后与前半段链表一一比对
class Solution {
    ListNode *reverseNode(ListNode *head) {
        ListNode *cur = head, *prev = nullptr;
        while (cur) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }

public:
    bool isPalindrome(ListNode *head) {
        if (!head->next)
            return true;
        if (!head->next->next)
            return head->val == head->next->val;
        ListNode *slow = head, *fast = head->next->next;
        while (fast) {
            slow = slow->next;
            fast = fast->next;
            if (fast)
                fast = fast->next;
        }
        ListNode *second = reverseNode(slow->next);
        ListNode *first = head;
        while (second) {
            if (second->val != first->val)
                return false;
            first = first->next;
            second = second->next;
        }
        return true;
    }
};

// int main() {
//     ListNode n4(1);
//     ListNode n3(2, &n4);
//     ListNode n2(2, &n3);
//     ListNode n1(1, &n2);
//     Solution sl;
//     std::cout << sl.isPalindrome(&n1) << std::endl;
//     return 0;
// }
