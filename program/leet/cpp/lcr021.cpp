//
// Created by Administrator on 2026/7/12.
//
/**
* LCR 021. 删除链表的倒数第 N 个结点
中等
相关标签
premium lock icon
相关企业
给定一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。



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


进阶：能尝试使用一趟扫描实现吗？
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
using namespace std;

//使用指针遍历到最后一个节点，然后尾递归方式返回，从倒数第一个结点往前数，从1开始数直到找到第n个删除即可
class Solution {
public:
    void removeCount(ListNode *cur, int n, int &count) {
        ListNode *next = cur->next;
        //递归找到最后一个节点，开始计数
        if (!next) {
            count = 1;
            return;
        }
        removeCount(next, n, count);
        //count =n ,当前节点为倒数第n+1个节点，需要删除后一个节点
        if (count > n)
            return;
        if (count == n) {
            cur->next = next->next;
            next->next = nullptr;
            // delete next;
        }
        //如果小于n，则++，大于后直接返回即可
        count++;
    }

    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (!head->next)
            return nullptr;
        ListNode sentinel(0, head);
        int count = 0;
        removeCount(&sentinel, n, count);
        return sentinel.next;
    }
};

// int main() {
//     //head = [1,2,3,4,5], n = 2
//     ListNode l5(5, nullptr);
//     ListNode l4(4, &l5);
//     ListNode l3(3, &l4);
//     ListNode l2(2, &l3);
//     ListNode l1(1, &l2);
//     Solution sl;
//     ListNode *node = sl.removeNthFromEnd(&l1, 2);
//     while (node) {
//         cout << node->val << " ";
//         node = node->next;
//     }
//     return 0;
// }
