//
// Created by Administrator on 2026/6/23.
//
/**
*
代码
测试用例
测试用例
测试结果
328. 奇偶链表
中等
相关标签
premium lock icon
相关企业
给定单链表的头节点 head ，将所有索引为奇数的节点和索引为偶数的节点分别分组，保持它们原有的相对顺序，然后把偶数索引节点分组连接到奇数索引节点分组之后，返回重新排序的链表。

第一个节点的索引被认为是 奇数 ， 第二个节点的索引为 偶数 ，以此类推。

请注意，偶数组和奇数组内部的相对顺序应该与输入时保持一致。

你必须在 O(1) 的额外空间复杂度和 O(n) 的时间复杂度下解决这个问题。



示例 1:



输入: head = [1,2,3,4,5]
输出: [1,3,5,2,4]
示例 2:



输入: head = [2,1,3,5,6,4,7]
输出: [2,3,6,7,1,5,4]


提示:

n ==  链表中的节点数
0 <= n <= 104
-106 <= Node.val <= 106
 * @return
 */
#include <stdlib.h>

#include "../node/listnode.h"

#define LISTNODE struct ListNode*

struct ListNode *oddEvenList(struct ListNode *head) {
    //少于2个节点直接返回
    if (!head || !head->next || !head->next->next)
        return head;
    //超过2个节点，新建2个哨兵节点开始拼装
    struct ListNode odd_sentinel = {-1,NULL};
    struct ListNode even_sentinel = {-1,NULL};
    LISTNODE odd = &odd_sentinel;
    LISTNODE even = &even_sentinel;
    LISTNODE cur = head;
    int i = 1;
    while (cur) {
        //奇数，放入奇数链表
        if (i & 1) {
            odd->next = cur;
            odd = odd->next;
        } else {
            even->next = cur;
            even = even->next;
        }
        cur = cur->next;
        i++;
    }
    even->next = NULL;
    odd->next = even_sentinel.next;
    return odd_sentinel.next;
}

int main() {
    return 0;
}
