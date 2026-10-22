//
// Created by Administrator on 2026/6/3.
//
/**
* 234. 回文链表
简单
相关标签
premium lock icon
相关企业
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。



示例 1：


输入：head = [1,2,2,1]
输出：true
示例 2：


输入：head = [1,2]
输出：false


提示：

链表中节点数目在范围[1, 105] 内
0 <= Node.val <= 9


进阶：你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？
 * @return
 */
#include "../node/listnode.h"
#include <stddef.h>
#include <stdio.h>

#include "stack.h"
//快慢指针，快指针移动到尾部，慢指针移动到中间
//快指针记录长度，慢指针往栈内压入数据
//当快指针到头，从慢指针开始弹栈
#define LISTNODE struct  ListNode *
typedef struct ListNode ListNode;
bool isPalindrome(struct ListNode* head) {
    if (!head->next)
        return true;
    //初始化栈
    Stack stack={0};
    init(&stack);
    int size =2;
    LISTNODE slowPtr =head;
    LISTNODE fastPtr = head->next->next;
    while (fastPtr) {
        size++;
        push(&stack,slowPtr->val);
        slowPtr=slowPtr->next;
        fastPtr = fastPtr->next;
        //如果fast的下一个为空，直接退出
        if (!fastPtr)
            break;
        //否则size+1，并指向下一个
        size++;
        fastPtr=fastPtr->next;
    }
    //统计完成size与压栈的数量
    //判断size是奇数还是偶数
    if ((size & 1)==0)
        //偶数就需要把当前慢指针数据压上
        push(&stack,slowPtr->val);
    slowPtr=slowPtr->next;
    while (slowPtr) {
        //不等于，直接返回
        if (slowPtr->val != pop(&stack))
            return false;
        slowPtr=slowPtr->next;
    }
    return true;
}

// int main() {
//     // struct ListNode l5 = {9, NULL};
//     struct ListNode l4 = {1, NULL};
//     struct ListNode l3 = {2, &l4};
//     struct ListNode l2 = {2, &l3};
//     struct ListNode l1 = {1, &l2};
//     printf("%d \n",isPalindrome(&l1));
//     return 0;
// }