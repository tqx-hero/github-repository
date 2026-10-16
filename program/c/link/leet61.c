//
// Created by Administrator on 2026/6/1.
//
/**
 *
*61. 旋转链表
￼
尝试过
￼
中等
￼
相关标签
￼
相关企业
￼
给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。 
示例 1：
输入：
head = [1,2,3,4,5], k = 2
输出：
[4,5,1,2,3]
示例 2：
输入：
head = [0,1,2], k = 4
输出：
[2,0,1]
  提示：
• 链表中节点的数目在范围 [0, 500] 内
• -100 <= Node.val <= 100
• 0 <= k <= 2 * 109
 */
#include <stddef.h>
#include <stdio.h>

#include "../node/listnode.h"

typedef struct ListNode *ListNode;

struct ListNode *rotateRight(struct ListNode *head, int k) {
    if (k == 0)
        return head;
    //计算链表长度
    int size = 0;
    ListNode cur = head, end = head;
    while (cur) {
        size++;
        end = cur;
        cur = cur->next;
    }
    //长度不超过1，直接返回head
    if (size <= 1)
        return head;
    int m = k % size;
    if (m == 0)
        return head;
    //计算需要放到链表末尾的节点最大长度
    m = size - m;
    cur = head;
    for (int i = 0; i < m - 1; ++i) {
        cur = cur->next;
    }
    ListNode tmp = cur->next;
    end->next = head;
    cur->next = NULL;
    head = tmp;
    return head;
}

// int main() {
//     // struct ListNode l5 = {5,NULL};
//     // struct ListNode l4 = {4, &l5};
//     // struct ListNode l3 = {3, &l4};
//     // struct ListNode l2 = {2, &l3};
//     struct ListNode l2 = {2, NULL};
//     struct ListNode l1 = {1, &l2};
//     struct ListNode *node = rotateRight(&l1, 1);
//     ListNode lptr = node;
//     while (lptr) {
//         printf("%d ", lptr->val);
//         lptr = lptr->next;
//     }
//     return 0;
// }
