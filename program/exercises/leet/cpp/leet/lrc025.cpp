//
// Created by Administrator on 2026/7/13.
//

/**
* LCR 025. 两数相加 II
中等
相关标签
premium lock icon
相关企业
给定两个 非空链表 l1和 l2 来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

可以假设除了数字 0 之外，这两个数字都不会以零开头。



示例 1：



输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]
示例 2：

输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[8,0,7]
示例 3：

输入：l1 = [0], l2 = [0]
输出：[0]


提示：

链表的长度范围为 [1, 100]
0 <= node.val <= 9
输入数据保证链表代表的数字无前导 0


进阶：如果输入链表不能修改该如何处理？换句话说，不能对列表中的节点进行翻转。
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
#include <stack>
using namespace std;

class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        stack<int> stack;
        ListNode *cur1 = l1;
        while (cur1) {
            stack.push(cur1->val);
            cur1 = cur1->next;
        }
        int carray = 0;
        add_linked_val(l2, stack, carray);
        //如果栈不为空或者有进位，则开始新建节点，头插法往head上插入
        ListNode *result = l2;
        while (carray || !stack.empty()) {
            ListNode *cur = new ListNode(0, result);
            cur->val = get_link_val(cur->val, stack, carray);
            result = cur;
        }
        return result;
    }

    int get_link_val(int val, stack<int> &stack, int &carray) {
        int num;
        if (!stack.empty()) {
            num = val + stack.top() + carray;
            stack.pop();
        } else
            num = val + carray;
        carray = num < 10 ? 0 : 1;
        num = num < 10 ? num : num - 10;
        return num;
    }

    void add_linked_val(ListNode *l2, stack<int> &stack, int &carray) {
        if (!l2->next) {
            l2->val = get_link_val(l2->val, stack, carray);
            return;
        }
        add_linked_val(l2->next, stack, carray);
        l2->val = get_link_val(l2->val, stack, carray);
    }
};

// int main() {
//     //l1 = [7,2,4,3], l2 = [5,6,4]
//     ListNode *l4 = new ListNode(3, nullptr);
//     ListNode *l3 = new ListNode(4, l4);
//     ListNode *l2 = new ListNode(2, l3);
//     ListNode *l1 = new ListNode(7, l2);
//
//     ListNode *l13 = new ListNode(4, nullptr);
//     ListNode *l12 = new ListNode(6, l13);
//     ListNode *l11 = new ListNode(5, l12);
//     Solution sl;
//     ListNode *numbers = sl.addTwoNumbers(l1, l11);
//     while (numbers) {
//         cout << numbers->val << " ";
//         numbers = numbers->next;
//     }
//     return 0;
// }
