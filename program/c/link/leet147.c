//
// Created by Administrator on 2026/6/18.
//
/**
* 147. 对链表进行插入排序
中等
相关标签
premium lock icon
相关企业
给定单个链表的头 head ，使用 插入排序 对链表进行排序，并返回 排序后链表的头 。

插入排序 算法的步骤:

插入排序是迭代的，每次只移动一个元素，直到所有元素可以形成一个有序的输出列表。
每次迭代中，插入排序只从输入数据中移除一个待排序的元素，找到它在序列中适当的位置，并将其插入。
重复直到所有输入数据插入完为止。
下面是插入排序算法的一个图形示例。部分排序的列表(黑色)最初只包含列表中的第一个元素。每次迭代时，从输入数据中删除一个元素(红色)，并就地插入已排序的列表中。

对链表进行插入排序。





示例 1：



输入: head = [4,2,1,3]
输出: [1,2,3,4]
示例 2：



输入: head = [-1,5,3,4,0]
输出: [-1,0,3,4,5]


提示：

列表中的节点数在 [1, 5000]范围内
-5000 <= Node.val <= 5000
 * @return
 */
#include <stdio.h>
#include <stdlib.h>

#include "../node/listnode.h"
#define LISTNODE struct ListNode*

struct ListNode *insertionSortList(struct ListNode *head) {
    if (!head->next)
        return head;
    int node_arr[5001];
    int size = 0;
    LISTNODE cur = head;
    while (cur) {
        node_arr[++size] = cur->val;
        cur = cur->next;
    }
    for (int i = 2; i <= size; ++i) {
        node_arr[0] = node_arr[i];
        int j = i;
        for (; j >= 1 && node_arr[0] < node_arr[j - 1]; --j)
            node_arr[j] = node_arr[j - 1];
        node_arr[j] = node_arr[0];
    }
    cur = head;
    for (int i = 1; i <= size; ++i) {
        cur->val = node_arr[i];
        cur = cur->next;
    }
    return head;
}

int main() {
    struct ListNode l4 = {3,NULL};
    struct ListNode l3 = {1, &l4};
    struct ListNode l2 = {2, &l3};
    struct ListNode l1 = {4, &l2};
    LISTNODE ret = insertionSortList(&l1);
    while (ret) {
        printf("%d ", ret->val);
        ret = ret->next;
    }
    return 0;
}
