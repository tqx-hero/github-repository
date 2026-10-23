#include <iostream>

#include "../link/ListNode.h"
class ListNode;
//
// Created by Administrator on 2026/7/3.
//
/**
* LCR 027. 回文链表
简单
相关标签
premium lock icon
相关企业
给定一个链表的 头节点 head ，请判断其是否为回文链表。

如果一个链表是回文，那么链表节点序列从前往后看和从后往前看是相同的。



示例 1：



输入: head = [1,2,3,3,2,1]
输出: true
示例 2：



输入: head = [1,2]
输出: false


提示：

链表 L 的长度范围为 [1, 105]
0 <= node.val <= 9


进阶：能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 * @return
 */
class Solution {
public:
    bool isPalindrome(ListNode *head) {
        ListNode *cur = head;
        //先统计链表长度
        int count = 0, i = 0;
        while (cur) {
            count++;
            cur = cur->next;
        }
        int *arr = new int[count];
        cur = head;
        while (cur) {
            *(arr + i++) = cur->val;
            cur = cur->next;
        }
        int mid = (count - 1) >> 1;
        bool flag = true;
        for (i = 0; i <= mid; i++) {
            if (arr[i] != arr[count - 1 - i]) {
                flag = false;
                goto ret;
            }
        }
    ret:
        delete[] arr;
        return flag;
    }
};

// int main() {
//     ListNode *n7 = new ListNode(1, nullptr);
//     ListNode *n6 = new ListNode(2, n7);
//     ListNode *n5 = new ListNode(3, n6);
//     ListNode *n4 = new ListNode(4, n5);
//     ListNode *n3 = new ListNode(3, n4);
//     ListNode *n2 = new ListNode(2, n3);
//     ListNode *n1 = new ListNode(1, n2);
//     Solution *sl = new Solution();
//     std::cout << "result = " << sl->isPalindrome(n1) << std::endl;
//     delete n1;
//     delete n2;
//     delete n3;
//     delete n4;
//     delete n5;
//     delete n6;
//     delete n7;
//     delete sl;
//     return 0;
// }
