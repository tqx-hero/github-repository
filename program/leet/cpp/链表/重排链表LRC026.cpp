//
// Created by Administrator on 2026/7/24.
//
/**
* LCR 026. 重排链表
中等
相关标签
premium lock icon
相关企业
给定一个单链表 L 的头节点 head ，单链表 L 表示为：

 L0 → L1 → … → Ln-1 → Ln
请将其重新排列后变为：

L0 → Ln → L1 → Ln-1 → L2 → Ln-2 → …

不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。



示例 1：



输入: head = [1,2,3,4]
输出: [1,4,2,3]
示例 2：



输入: head = [1,2,3,4,5]
输出: [1,5,2,4,3]


提示：

链表的长度范围为 [1, 5 * 104]
1 <= node.val <= 1000
 * @return
 */
#include <cstddef>
#include <stdexcept>

#include "../../link/ListNode.h"

class Solution {
public:
    void reorderList(ListNode *head) {
        if (!head->next || !head->next->next)
            return;
        ListNode dummy(0, head);
        ListNode *slow = head, *fast = head->next->next;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
            if (!fast->next)
                break;
            fast = fast->next;
        }
        ListNode *second = reverse(slow->next), *cur = &dummy, *one = head;
        slow->next = nullptr;
        while (second && one) {
            ListNode *oneNext = one->next, *secondNext = second->next;
            cur->next = one;
            cur = cur->next;
            one = oneNext;
            cur->next = second;
            cur = cur->next;
            second = secondNext;
        }
        cur->next = one ? one : second;
    }

private:
    ListNode *reverse(ListNode *node) {
        if (!node)
            throw std::invalid_argument("链表不能为空!");
        ListNode *cur = node, *prev = nullptr;
        while (cur) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

// int main() {
//     return 0;
// }
