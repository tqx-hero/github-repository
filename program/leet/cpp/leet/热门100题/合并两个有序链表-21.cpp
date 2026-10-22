//
// Created by 田庆新 on 2026/9/2.
//
/**
* 21. 合并两个有序链表
已解答
简单
相关标签
premium lock icon
相关企业
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。



示例 1：


输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
示例 2：

输入：l1 = [], l2 = []
输出：[]
示例 3：

输入：l1 = [], l2 = [0]
输出：[0]


提示：

两个链表的节点数目范围是 [0, 50]
-100 <= Node.val <= 100
l1 和 l2 均按 非递减顺序 排列
 * @return
 */
#include "../../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        if (!list1 || !list2)
            return list1 ? list1 : list2;
        ListNode dummy(-1);
        ListNode *cur = &dummy;
        while (list1 && list2) {
            if (list1->val <= list2->val) {
                cur->next = list1;
                list1 = list1->next;
            } else {
                cur->next = list2;
                list2 = list2->next;
            }
            cur = cur->next;
        }
        cur->next = list1 ? list1 : list2;
        return dummy.next;
    }
};

// int main() {
//     return 0;
// }
