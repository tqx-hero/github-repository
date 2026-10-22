//
// Created by Administrator on 2026/7/15.
//

/**
*面试题 02.04. 分割链表
中等
相关标签
premium lock icon
相关企业
提示
给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。

你不需要 保留 每个分区中各节点的初始相对位置。



示例 1：


输入：head = [1,4,3,2,5,2], x = 3
输出：[1,2,2,4,3,5]
示例 2：

输入：head = [2,1], x = 2
输出：[1,2]


提示：

链表中节点的数目在范围 [0, 200] 内
-100 <= Node.val <= 100
-200 <= x <= 200
*/
#include "../link/ListNode.h"

class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if (!head || !head->next)
            return head;
        ListNode *prev, *cur = head;
        //找到第一个大于等于x的节点，设置其为prev
        while (cur && cur->val < x)
            cur = cur->next;
        if (!cur)
            return head;
        prev = cur;
        cur = cur->next;
        while (cur) {
            if (cur->val < x) {
                int temp = cur->val;
                cur->val = prev->val;
                prev->val = temp;
                prev = prev->next;
            }
            cur = cur->next;
        }
        return head;
    }
};

// int main() {
//     return 0;
// }
