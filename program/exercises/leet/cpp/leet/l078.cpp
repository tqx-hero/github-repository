//
// Created by Administrator on 2026/7/19.
//
/**
* LCR 078. 合并 K 个升序链表
困难
相关标签
premium lock icon
相关企业
给定一个链表数组，每个链表都已经按升序排列。

请将所有链表合并到一个升序链表中，返回合并后的链表。



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
#include "../link/ListNode.h"
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *mergeKLists(vector<ListNode *> &lists) {
        //分治，将整个数组拆分成一个个子数组，每个数组再拆分，直到数组仅剩下2个元素，每个元素对应一个链表。
        //进行链表合并，条件既然是已经升序的链表，那就按照链表合并的方式进行合并。
        //合并后逐层返回，最后返回结果
        int size = lists.size();
        if (!size)
            return nullptr;
        return merge(lists, 0, size - 1);
    }

private:
    ListNode *merge(vector<ListNode *> &lists, int left, int right) {
        if (left == right)
            return lists.at(left);
        int mid = left + (right - left) / 2;
        return mergeList(merge(lists, left, mid), merge(lists, mid + 1, right));
    }

    ListNode *mergeList(ListNode *l1, ListNode *l2) {
        if (!l1 || !l2)
            return l1 ? l1 : l2;
        ListNode sentinel(0), *cur = &sentinel;
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
        return sentinel.next;
    }
};


// int main() {
//     vector<ListNode *> list;
//     //lists = [[1,4,5],[1,3,4],[2,6]]
//     ListNode l3(5);
//     ListNode l2(4, &l3);
//     ListNode l1(1, &l2);
//
//     ListNode l6(4);
//     ListNode l5(3, &l6);
//     ListNode l4(1, &l5);
//
//     ListNode l8(6);
//     ListNode l7(2, &l8);
//     list.push_back(&l1);
//     list.push_back(&l4);
//     list.push_back(&l7);
//
//     Solution sl;
//     auto node = sl.mergeKLists(list);
//     while (node) {
//         cout << node->val << " ";
//         node = node->next;
//     }
//     return 0;
// }
