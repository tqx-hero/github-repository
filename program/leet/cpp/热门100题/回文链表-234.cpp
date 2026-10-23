//
// Created by 田庆新 on 2026/9/2.
//
/**
* 234. 回文链表
已解答
简单
相关标签
premium lock icon
相关企业
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。



示例 1：


输入：head = [1,2,2,1]
输出：true
示例 2：


输入：head = [1,2]
输出：false


提示：

链表中节点数目在范围[1, 105] 内
0 <= Node.val <= 9


进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 * @return
 */
#include "../../link/ListNode.h"

class Solution {
    ListNode *reverse_right(ListNode *node) {
        ListNode *cur = node, *prev = nullptr;
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
        //快慢指针
        ListNode *slow = head, *fast = head->next->next;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
            if (fast->next)
                fast = fast->next;
        }
        //从慢指针的next开始往后反转链表,别忘了断掉前半段最后
        ListNode *second = reverse_right(slow->next);
        slow->next = nullptr;
        ListNode *first = head;
        while (first && second) {
            if (first->val != second->val)
                return false;
            first = first->next;
            second = second->next;
        }
        return true;
    }
};

// int main() {
//     return 0;
// }
