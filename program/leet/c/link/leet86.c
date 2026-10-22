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
86. 分隔链表
￼
中等
￼
相关标签
￼
相关企业
￼
给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
你应当 保留 两个分区中每个节点的初始相对位置。 
示例 1：
输入：
head = [1,4,3,2,5,2], x = 3
输出
：[1,2,2,4,3,5]
示例 2：
输入：
head = [2,1], x = 2
输出
：[1,2]
  提示：
• 链表中节点的数目在范围 [0, 200] 内
• -100 <= Node.val <= 100
• -200 <= x <= 200
 * @return
 */
#include <stdio.h>
#include <stdlib.h>

#include "../node/listnode.h"
#define LISTNODEPTR  struct  ListNode*
typedef struct ListNode ListNode;

struct ListNode *partition(struct ListNode *head, int x) {
    if (!head || !head->next)
        return head;
    LISTNODEPTR cur = head;
    int size = sizeof(ListNode);
    LISTNODEPTR sentinel = malloc(size);
    sentinel->next = NULL;
    LISTNODEPTR resCur = sentinel;

    LISTNODEPTR b_sentinel = malloc(size);
    b_sentinel->next = NULL;
    LISTNODEPTR bigCur = b_sentinel;
    while (cur) {
        int val = cur->val;
        //大于等于x的添加到较大链表
        if (val >= x) {
            bigCur->next = cur;
            bigCur = bigCur->next;
        }
        //小于的则新建节点添加到链表中
        else {
            resCur->next = cur;
            resCur = resCur->next;
        }
        cur = cur->next;
    }
    bigCur->next = NULL;
    resCur->next = b_sentinel->next;
    LISTNODEPTR resptr = sentinel->next;
    free(sentinel);
    sentinel = NULL;
    free(b_sentinel);
    b_sentinel = NULL;
    return resptr;
}

// int main() {
//     struct ListNode l6 = {2,NULL};
//     struct ListNode l5 = {5, &l6};
//     struct ListNode l4 = {2, &l5};
//     struct ListNode l3 = {3, &l4};
//     struct ListNode l2 = {4, &l3};
//     struct ListNode l1 = {1, &l2};
//     struct ListNode *node = partition(&l1, 3);
//     LISTNODEPTR lptr = node;
//     while (lptr) {
//         printf("%d ", lptr->val);
//         lptr = lptr->next;
//     }
//     return 0;
// }
