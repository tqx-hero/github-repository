//
// Created by Administrator on 2026/7/11.
//
/**
* 2816. 翻倍以链表形式表示的数字
中等
相关标签
premium lock icon
相关企业
提示
给你一个 非空 链表的头节点 head ，表示一个不含前导零的非负数整数。

将链表 翻倍 后，返回头节点 head 。



示例 1：


输入：head = [1,8,9]
输出：[3,7,8]
解释：上图中给出的链表，表示数字 189 。返回的链表表示数字 189 * 2 = 378 。
示例 2：


输入：head = [9,9,9]
输出：[1,9,9,8]
解释：上图中给出的链表，表示数字 999 。返回的链表表示数字 999 * 2 = 1998 。


提示：

链表中节点的数目在范围 [1, 104] 内
0 <= Node.val <= 9
生成的输入满足：链表表示一个不含前导零的数字，除了数字 0 本身。
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    int get_num(int num, int &carray) {
        num = (num << 1) + carray;
        carray = num < 10 ? 0 : 1;
        return num < 10 ? num : num - 10;
    }

    void calculate(ListNode *cur, int &carray) {
        //找到最后一个节点,开始计算结果
        if (!cur->next) {
            cur->val = get_num(cur->val, carray);
            return;
        }
        calculate(cur->next, carray);
        cur->val = get_num(cur->val, carray);
    }

    ListNode *doubleIt(ListNode *head) {
        ListNode *sentinel = new ListNode(0, head);
        int carray = 0;
        calculate(sentinel, carray);
        if (sentinel->val == 1)
            return sentinel;
        sentinel->next = nullptr;
        delete sentinel;
        return head;
    }
};

// int main() {
//     ListNode *l3 = new ListNode(9, nullptr);
//     ListNode *l2 = new ListNode(9, l3);
//     ListNode *l1 = new ListNode(9, l2);
//     Solution sl;
//     ListNode *node = sl.doubleIt(l1);
//     while (node) {
//         cout << node->val << endl;
//         ListNode *next = node->next;
//         delete node;
//         node = next;
//     }
//     return 0;
// }
