//
// Created by Administrator on 2026/6/1.
//
/**
*
￼
代码
￼
测试用例
测试用例
￼
测试结果
92. 反转链表 II
￼
中等
￼
相关标签
￼
相关企业
￼
给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。 
示例 1：
输入：
head = [1,2,3,4,5], left = 2, right = 4
输出：
[1,4,3,2,5]
示例 2：
输入：
head = [5], left = 1, right = 1
输出：
[5]
  提示：
• 链表中节点数目为 n
• 1 <= n <= 500
• -500 <= Node.val <= 500
• 1 <= left <= right <= n 
进阶： 你可以使用一趟扫描完成反转吗？
 * @return
 */
#include <stdio.h>
#include <stdlib.h>

#include "../node/listnode.h"
#define LISTNODEPTR  struct  ListNode*
typedef struct ListNode ListNode;

struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    if (!head->next || left == right)
        return head;
    LISTNODEPTR sentinel =  malloc(sizeof(ListNode));
    sentinel->next = head;
    LISTNODEPTR beforeNode = sentinel;
    //找出第left-1个节点与第right+1个节点
    int i = 0;
    for (; i < left - 1; ++i)
        beforeNode = beforeNode->next;
    //找到第right+1个节点
    LISTNODEPTR afterNode=beforeNode;
    for (;i<=right;i++)
        afterNode = afterNode->next;
    //翻转从left到right
    LISTNODEPTR cur = beforeNode->next;
    LISTNODEPTR prev = afterNode;
    while (cur !=afterNode) {
        LISTNODEPTR tmpPtr = cur->next;
        cur->next =prev;
        prev = cur;
        cur = tmpPtr;
    }
    beforeNode->next=prev;
    LISTNODEPTR resPtr = sentinel->next;
    free(sentinel);
    sentinel=NULL;
    return resPtr;
}

// int main() {
//     struct ListNode l5 = {5, NULL};
//     struct ListNode l4 = {4, &l5};
//     struct ListNode l3 = {3, &l4};
//     struct ListNode l2 = {2, &l3};
//     struct ListNode l1 = {1, &l2};
//     struct ListNode *node = reverseBetween(&l1, 2,4);
//     LISTNODEPTR lptr = node;
//     while (lptr) {
//         printf("%d ", lptr->val);
//         lptr = lptr->next;
//     }
//     return 0;
// }
