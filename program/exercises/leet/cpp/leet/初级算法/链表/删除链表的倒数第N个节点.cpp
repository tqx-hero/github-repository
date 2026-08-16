//
// Created by Administrator on 2026/8/12.
//
/**
* 删除链表的倒数第N个节点
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。 
示例 1：
输入：head = [1,2,3,4,5], n = 2

输出：[1,2,3,5]

示例 2：
输入：head = [1], n = 1

输出：[]

示例 3：
输入：head = [1,2], n = 1

输出：[1]
  
提示：
• 链表中结点的数目为 sz
• 1 <= sz <= 30
• 0 <= Node.val <= 100
• 1 <= n <= sz 
进阶：你能尝试使用一趟扫描实现吗？
 * @return
 */
#include "../../../link/ListNode.h"

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        //定义两个指针，间距差n，当右指针right到末尾时，左指针left->next则为要删除的节点
        if (!head->next)
            return nullptr;
        ListNode *left = head, *right = head;
        while (n && right->next) {
            right = right->next;
            n--;
        }
        if (n)
            return head->next;
        //遍历到头
        while (right->next) {
            right = right->next;
            left = left->next;
        }
        //去掉left->next节点即可
        left->next = left->next->next;
        return head;
    }
};

// int main() {
//     return 0;
// }
