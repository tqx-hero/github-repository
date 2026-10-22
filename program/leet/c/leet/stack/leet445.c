//
// Created by Administrator on 2026/6/6.
//
/**
*
代码
测试用例
测试用例
测试结果
445. 两数相加 II
中等
相关标签
premium lock icon
相关企业
给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。

你可以假设除了数字 0 之外，这两个数字都不会以零开头。



示例1：



输入：l1 = [7,2,4,3], l2 = [5,6,4]
输出：[7,8,0,7]
示例2：

输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[8,0,7]
示例3：

输入：l1 = [0], l2 = [0]
输出：[0]


提示：

链表的长度范围为 [1, 100]
0 <= node.val <= 9
输入数据保证链表代表的数字无前导 0


进阶：如果输入链表不能翻转该如何解决？
 * @return
 */
#include <stdio.h>
#include <stdlib.h>

#include "../node/listnode.h"

#define  LISTNODE struct ListNode*
typedef struct ListNode ListNode;
struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {
    LISTNODE arr1[101];
    LISTNODE arr2[101];
    LISTNODE l1Ptr = l1;
    LISTNODE l2Ptr = l2;
    int i = 0, j = 0;
    while (l1Ptr) {
        *(arr1 + i++) = l1Ptr;
        l1Ptr = l1Ptr->next;
    }
    while (l2Ptr) {
        *(arr2 + j++) = l2Ptr;
        l2Ptr = l2Ptr->next;
    }
    //拼接链表
    LISTNODE cur = NULL;
    int cf = 0;
    for (i--, j--; i >= 0 || j >= 0; ) {
        //只剩下l2
        int result;
        if (i <0) {
            LISTNODE node2 = *(arr2 + j);
            result = node2->val + cf;
            j--;
        }else if (j<0) {
            //只剩下l1
            LISTNODE node1 = *(arr1 + i);
            result = node1->val + cf;
            i--;
        }else {
            //全部都有
            LISTNODE node1 = *(arr1 + i);
            LISTNODE node2 = *(arr2 + j);
            result = node1->val + node2->val + cf;
            i--;
            j--;
        }
        if (result > 9) {
            cf = 1;
            result -= 10;
        } else
            cf = 0;
        LISTNODE node = malloc(sizeof(ListNode));
        node->val=result;
        node->next=cur;
        cur =node;
    }
    //如果仍有进位，在创建头节点
    if (cf) {
        LISTNODE node = malloc(sizeof(ListNode));
        node->val=1;
        node->next=cur;
        cur =node;
    }
    return cur;
}

// int main() {
//
//     ListNode l4={3,NULL};
//     ListNode l3={4,&l4};
//     ListNode l2={5,&l3};
//     ListNode l1={9,&l2};
//
//     ListNode l7={4,NULL};
//     ListNode l6={6,&l7};
//     ListNode l5={5,&l6};
//
//     LISTNODE node = addTwoNumbers(&l1,&l5);
//     while (node) {
//         LISTNODE cur= node;
//         printf("%d ",cur->val);
//         node=node->next;
//         free(cur);
//         cur=NULL;
//     }
//     return 0;
// }
