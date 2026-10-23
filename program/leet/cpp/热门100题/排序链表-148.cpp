//
// Created by 田庆新 on 2026/9/3.
//
/**
* 148. 排序链表
已解答
中等
相关标签
premium lock icon
相关企业
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。



示例 1：


输入：head = [4,2,1,3]
输出：[1,2,3,4]
示例 2：


输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]
示例 3：

输入：head = []
输出：[]


提示：

链表中节点的数目在范围 [0, 5 * 104] 内
-105 <= Node.val <= 105


进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
 * @return
 */
#include "../../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
    ListNode *merge(ListNode *l1, ListNode *l2) {
        ListNode dummy(0), *cur = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return dummy.next;
    }

public:
    ListNode *sortList(ListNode *head) {
        if (!head || !head->next)
            return head;
        //归并排序
        //快慢指针找到链表中间节点
        ListNode *slow = head, *fast = head;
        while (fast->next && fast->next->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        //slow.next为后面链表的起始节点
        ListNode *left = head, *right = slow->next;
        //断开slow与后面节点的联系
        slow->next = nullptr;
        return merge(sortList(left), sortList(right));
    }
};

// int main() {
//     return 0;
// }
