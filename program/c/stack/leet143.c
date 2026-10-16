//
// Created by Administrator on 2026/6/5.
//
/**
*
代码
测试用例
测试用例
测试结果
143. 重排链表
中等
相关标签
premium lock icon
相关企业
给定一个单链表 L 的头节点 head ，单链表 L 表示为：

L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。



示例 1：



输入：head = [1,2,3,4]
输出：[1,4,2,3]
示例 2：



输入：head = [1,2,3,4,5]
输出：[1,5,2,4,3]


提示：

链表的长度范围为 [1, 5 * 104]
1 <= node.val <= 1000
 * @return
 */
#include <stdlib.h>

# include  "../node/listnode.h"
#define LISTNODE struct ListNode*
#define ARR_MAX_SIZE 50001
typedef struct ListNode ListNode;
void reorderList(struct ListNode* head) {
    LISTNODE cur = head;
    LISTNODE arr[ARR_MAX_SIZE];
    int i=0;
    while (cur) {
        arr[i++] = cur;
        cur =cur->next;
    }
    //根据长度左右指针开始拼接
    LISTNODE sentinel = malloc(sizeof(ListNode));
    sentinel->next=NULL;
    cur =sentinel;
    for (int left = 0,right =i-1; left<=right ; ++left,right--) {
        arr[left]->next = arr[right];
        cur->next = arr[left];
        cur=arr[right];
    }
    cur->next=NULL;
    free(sentinel);
}

// int main() {
//     struct ListNode l5 = {5, NULL};
//     struct ListNode l4 = {4, &l5};
//     struct ListNode l3 = {3, &l4};
//     struct ListNode l2 = {2, &l3};
//     struct ListNode l1 = {1, &l2};
//     reorderList(&l1);
//
//     return 0;
// }
