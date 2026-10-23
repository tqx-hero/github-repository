//
// Created by Administrator on 2026/7/8.
//

/**
* 2074. 反转偶数长度组的节点
中等
相关标签
premium lock icon
相关企业
提示
给你一个链表的头节点 head 。

链表中的节点 按顺序 划分成若干 非空 组，这些非空组的长度构成一个自然数序列（1, 2, 3, 4, ...）。一个组的 长度 就是组中分配到的节点数目。换句话说：

节点 1 分配给第一组
节点 2 和 3 分配给第二组
节点 4、5 和 6 分配给第三组，以此类推
注意，最后一组的长度可能小于或者等于 1 + 倒数第二组的长度 。

反转 每个 偶数 长度组中的节点，并返回修改后链表的头节点 head 。



示例 1：



输入：head = [5,2,6,3,9,1,7,3,8,4]
输出：[5,6,2,3,9,1,4,8,3,7]
解释：
- 第一组长度为 1 ，奇数，没有发生反转。
- 第二组长度为 2 ，偶数，节点反转。
- 第三组长度为 3 ，奇数，没有发生反转。
- 最后一组长度为 4 ，偶数，节点反转。
示例 2：



输入：head = [1,1,0,6]
输出：[1,0,1,6]
解释：
- 第一组长度为 1 ，没有发生反转。
- 第二组长度为 2 ，节点反转。
- 最后一组长度为 1 ，没有发生反转。
示例 3：



输入：head = [2,1]
输出：[2,1]
解释：
- 第一组长度为 1 ，没有发生反转。
- 最后一组长度为 1 ，没有发生反转。


提示：

链表中节点数目范围是 [1, 105]
0 <= Node.val <= 105
 * @return
 */
#include <iostream>
#include "../link/ListNode.h"
using namespace std;

//翻转链表
void reverse(ListNode *&prev, ListNode *&next) {
    ListNode *cur = prev->next, *prv = next;
    while (cur != next) {
        ListNode *nt = cur->next;
        cur->next = prv;
        prv = cur;
        cur = nt;
    }
    prev->next = prv;
}

int getNextPtr(ListNode *&cur, int jmpCount) {
    int i = 0;
    while (cur && i < jmpCount) {
        cur = cur->next;
        i++;
    }
    return i;
}

ListNode *reverseEvenLengthGroups(ListNode *head) {
    //小于2个节点，直接返回
    if (!head->next || !head->next->next)
        return head;
    int number = 2, count = 2;
    ListNode *prev = head, *next = head->next->next->next;
    bool flag = false;
    while ((flag = count && !(count & 0x1)) || next) {
        if (flag)
            //翻转这个区间的链表
            reverse(prev, next);
        //指针前进，更新它的区间奇偶性
        getNextPtr(prev, number++);
        if (!prev)
            break;
        //更新next
        count = getNextPtr(next, number);
    }
    return head;
}

// int main() {
//     //head = [5,2,6,3,9,1,7,3,8,4]
//     ListNode n10{4, nullptr};
//     ListNode n9{8, &n10};
//     ListNode n8{3, &n9};
//     ListNode n7{7, &n8};
//     ListNode n6{1, &n7};
//     ListNode n5{9, &n6};
//     ListNode n4{3, &n5};
//     ListNode n3{6, &n4};
//     ListNode n2{2, &n3};
//     ListNode n1{5, &n2};
//     ListNode *node = reverseEvenLengthGroups(&n1);
//     while (node) {
//         cout << node->val << endl;
//         node = node->next;
//     }
//     return 0;
// }
