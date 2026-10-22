//
// Created by Administrator on 2026/7/15.
//
/**
* 面试题 02.06. 回文链表
简单
相关标签
premium lock icon
相关企业
提示
编写一个函数，检查输入的链表是否是回文的。



示例 1：

输入： 1->2
输出： false
示例 2：

输入： 1->2->2->1
输出： true


进阶：
你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    bool isPalindrome(ListNode *head) {
        if (!head || !head->next)
            return true;
        ListNode *cur = head;
        int size = 0;
        //计算链表长度
        while (cur) {
            size++;
            cur = cur->next;
        }
        //翻转后半部分链表
        int half = (size + 1) >> 1, i = 1;
        cur = head;
        while (i++ < half)
            cur = cur->next;
        cur->next = reverseLinked(cur->next);
        return compare(head, cur->next);
    }

private:
    bool compare(ListNode *head, ListNode *cur) {
        while (cur) {
            if (cur->val != head->val)
                return false;
            cur = cur->next;
            head = head->next;
        }
        return true;
    }

    ListNode *reverseLinked(ListNode *root) {
        ListNode *cur = root, *prev = nullptr;
        while (cur) {
            auto next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};

// int main() {
//     ListNode l5(1);
//     ListNode l4(2, &l5);
//     ListNode l3(3, &l4);
//
//     ListNode l2(2, &l3);
//     ListNode l1(1, &l2);
//     Solution sl;
//     cout << sl.isPalindrome(&l1) << endl;
//     return 0;
// }
