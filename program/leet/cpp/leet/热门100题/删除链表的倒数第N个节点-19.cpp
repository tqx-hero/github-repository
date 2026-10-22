//
// Created by 田庆新 on 2026/9/2.
//
/**
* 19. 删除链表的倒数第 N 个结点
已解答
中等
相关标签
premium lock icon
相关企业
提示
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。



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

链表中结点的数目为 sz
1 <= sz <= 30
0 <= Node.val <= 100
1 <= n <= sz


进阶：你能尝试使用一趟扫描实现吗？
 * @return
 */
#include "../../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        //使用双指针，指针间隔n,快指针遍历到结尾时，慢指针的位置是要删除节点的前驱
        ListNode dummy(0, head);
        ListNode *slow = &dummy, *fast = slow;
        while (n--)
            fast = fast->next;
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        //去掉slow后面的节点
        slow->next = slow->next->next;
        return dummy.next;
    }
};

// int main() {
//     return 0;
// }
