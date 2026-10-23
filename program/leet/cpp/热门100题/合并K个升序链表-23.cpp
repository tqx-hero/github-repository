//
// Created by 田庆新 on 2026/9/3.
//
/**
* 23. 合并 K 个升序链表
已解答
困难
相关标签
premium lock icon
相关企业
给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。



示例 1：

输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：

输入：lists = []
输出：[]
示例 3：

输入：lists = [[]]
输出：[]


提示：

k == lists.length
0 <= k <= 10^4
0 <= lists[i].length <= 500
-10^4 <= lists[i][j] <= 10^4
lists[i] 按 升序 排列
lists[i].length 的总和不超过 10^4
 * @return
 */
#include "../../link/ListNode.h"
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    ListNode *merge(ListNode *l1, ListNode *l2) {
        if (!l1 || !l2)
            return l1 ? l1 : l2;
        ListNode dummy(0), *cur = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                cur->next = l1;
                l1 = l1->next;
            } else {
                cur->next = l2;
                l2 = l2->next;
            }
            cur = cur->next;
        }
        cur->next = l1 ? l1 : l2;
        return dummy.next;
    }

    ListNode *merge_array(vector<ListNode *> &lists, int left, int right) {
        if (left == right)
            return lists[left];
        int mid = left +(right-left)/2;
        return merge(merge_array(lists,left,mid),
            merge_array(lists,mid+1,right));
    }

public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        int size =static_cast<int>(lists.size());
        if (!size)
            return nullptr;
        return merge_array(lists, 0,  size- 1);
    }
};

// int main() {
//     return 0;
// }
