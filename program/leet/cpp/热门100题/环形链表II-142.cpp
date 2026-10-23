//
// Created by 田庆新 on 2026/9/2.
//
/**
* 142. 环形链表 II
已解答
中等
相关标签
premium lock icon
相关企业
给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

不允许修改 链表。



示例 1：



输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：



输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：



输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。


提示：

链表中节点的数目范围在范围 [0, 104] 内
-105 <= Node.val <= 105
pos 的值为 -1 或者链表中的一个有效索引


进阶：你是否可以使用 O(1) 空间解决此题？
 * @return
 */
#include "../../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next || !head->next->next)
            return nullptr;
        ListNode *slow = head, *fast = head;
        do {
            fast = fast->next->next;
            slow = slow->next;
        } while (fast->next && fast->next->next && fast != slow);
        if (fast != slow)
            return nullptr;
        ListNode *left = head, *right = slow;
        while (left != right) {
            left = left->next;
            right = right->next;
        }
        return left;
    }
};

// int main() {
//     //3,2,0,-4
//     ListNode l4(-4);
//     ListNode l3(0, &l4);
//     ListNode l2(2, &l3);
//     ListNode l1(3, &l2);
//     l4.next = &l2;
//     Solution sl;
//     ListNode *node = sl.detectCycle(&l1);
//     cout << node->val << endl;
//     return 0;
// }
