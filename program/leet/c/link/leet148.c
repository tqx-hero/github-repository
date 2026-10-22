//
// Created by Administrator on 2026/6/20.
//
/**
*
代码
测试用例
测试用例
测试结果
148. 排序链表
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
#include <stddef.h>
#include <stdlib.h>

#include "../node/listnode.h"
#define LISTNODE struct ListNode*

static int compare(const void *a, const void *b) {
    return *(int *) a - *(int *) b;
}

struct ListNode *sortList(struct ListNode *head) {
    if (!head)
        return NULL;
    int val_arr[50001], i = 0;
    LISTNODE cur = head;
    for (; cur; i++, cur = cur->next)
        val_arr[i] = cur->val;
    qsort(val_arr, i, sizeof(int), compare);
    cur = head;
    for (i = 0; cur; i++, cur = cur->next)
        cur->val = val_arr[i];
    return head;
}

int main() {
    return 0;
}
