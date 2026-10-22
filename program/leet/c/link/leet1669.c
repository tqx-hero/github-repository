//
// Created by Administrator on 2026/6/30.
//
/**
* 1669. 合并两个链表
中等
相关标签
premium lock icon
相关企业
提示
给你两个链表 list1 和 list2 ，它们包含的元素分别为 n 个和 m 个。

请你将 list1 中下标从 a 到 b 的全部节点都删除，并将list2 接在被删除节点的位置。

下图中蓝色边和节点展示了操作后的结果：


请你返回结果链表的头指针。



示例 1：



输入：list1 = [10,1,13,6,9,5], a = 3, b = 4, list2 = [1000000,1000001,1000002]
输出：[10,1,13,1000000,1000001,1000002,5]
解释：我们删除 list1 中下标为 3 和 4 的两个节点，并将 list2 接在该位置。上图中蓝色的边和节点为答案链表。
示例 2：


输入：list1 = [0,1,2,3,4,5,6], a = 2, b = 5, list2 = [1000000,1000001,1000002,1000003,1000004]
输出：[0,1,1000000,1000001,1000002,1000003,1000004,6]
解释：上图中蓝色的边和节点为答案链表。


提示：

3 <= list1.length <= 104
1 <= a <= b < list1.length - 1
1 <= list2.length <= 104
 * @return
 */

#include <string.h>

#include "../node/listnode.h"

struct ListNode *mergeInBetween(struct ListNode *list1, int a, int b, struct ListNode *list2) {
    int i = 0;
    struct ListNode *cur = list1;
    //跳过前a-1个节点,得到a节点的前一个结点
    while (i++ < a - 1)
        cur = cur->next;
    struct ListNode *next = cur->next;
    cur->next = list2;
    //找到新的list1节点尾部cur
    while (cur->next)
        cur = cur->next;
    //找到b的前一个节点
    for (i = a; i < b; i++)
        next = next->next;
    cur->next = next->next;
    next->next = NULL;
    return list1;
}

int main() {
    return 0;
}
