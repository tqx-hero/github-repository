//
// Created by Administrator on 2026/7/23.
//
/**
* LCR 077. 排序链表
中等
相关标签
premium lock icon
相关企业
给定链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。



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
#include "../../link/ListNode.h"
#include <iostream>
using namespace std;

class Solution {
public:
    ListNode *sortList(ListNode *head) {
        if (!head || !head->next)
            return head;
        //分割链表，先两两合并，这样1个合并成2个。
        //一圈下来再2个一组合并，这一趟合并成4个。
        //再下一圈，4个一组合并，使得每8个局部有序...
        //最后迭代直到组内元素增量大于等于链表总长度，停止返回即可
        ListNode sentinel(0, head);
        ListNode *cur = head, *prev, *tail;
        //先计算链表的总长度
        int count = 0, gap = 1;
        while (cur && ++count)
            cur = cur->next;
        while (gap < count) {
            prev = &sentinel, cur = prev->next;
            while (cur) {
                //截取gap长度的链表，返回各自的头部l1、l2
                ListNode *left = splitNode(prev, gap);
                if (!left || !left->next)
                    break;
                ListNode *leftNext = left->next;
                ListNode *right = splitNode(left, gap);
                ListNode *rightNext = nullptr;
                if (right) {
                    rightNext = right->next;
                    right->next = nullptr;
                }
                left->next = nullptr;
                //调用merge函数，将l1、l2合并成一个链表，做到局部有序，合并后与后面未排序的链表连起来
                if (leftNext) {
                    prev->next = merge(prev->next, leftNext, tail);
                    tail->next = rightNext;
                    prev = tail;
                    cur = prev->next;
                    tail = nullptr;
                } else
                    break;
                //继续遍历后面的链表，指向以上相同的操作。直到最后一个节点
                //增量乘以2，继续执行上述操作，直到gap超过count
            }
            gap <<= 1;
        }
        return sentinel.next;
    }

private:
    ListNode *splitNode(ListNode *cur, int length) {
        int i = 0;
        for (; i < length && cur; i++)
            cur = cur->next;
        return cur;
    }

    ListNode *merge(ListNode *l1, ListNode *l2, ListNode *&tail) {
        if (!l1 || !l2)
            return l1 ? l1 : l2;
        ListNode sentinel(0);
        ListNode *cur = &sentinel;
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
        while (cur->next)
            cur = cur->next;
        tail = cur;
        return sentinel.next;
    }
};

// int main() {
//     //[-1,5,3,4,0]
//     ListNode n5(0);
//     ListNode n4(4, &n5);
//     ListNode n3(3, &n4);
//     ListNode n2(5, &n3);
//     ListNode n1(-1, &n2);
//     // ListNode n4(3);
//     // ListNode n3(1, &n4);
//     // ListNode n2(2, &n3);
//     // ListNode n1(4, &n2);
//
//     Solution sl;
//     auto list = sl.sortList(&n1);
//     while (list) {
//         cout << list->val << endl;
//         list = list->next;
//     }
//     return 0;
// }
