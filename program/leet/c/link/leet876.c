//
// Created by Administrator on 2026/6/25.
//
/**
* 876. 链表的中间结点
简单
相关标签
premium lock icon
相关企业
给你单链表的头结点 head ，请你找出并返回链表的中间结点。

如果有两个中间结点，则返回第二个中间结点。



示例 1：


输入：head = [1,2,3,4,5]
输出：[3,4,5]
解释：链表只有一个中间结点，值为 3 。
示例 2：


输入：head = [1,2,3,4,5,6]
输出：[4,5,6]
解释：该链表有两个中间结点，值分别为 3 和 4 ，返回第二个结点。


提示：

链表的结点数范围是 [1, 100]
1 <= Node.val <= 100
 * @return
 */
#include <stddef.h>

#include "../node/listnode.h"
typedef struct ListNode *list_ptr;

struct ListNode *middleNode(struct ListNode *head) {
    //快慢指针解决
    if (!head->next)
        return head;
    if (!head->next->next)
        return head->next;
    list_ptr slow_ptr = head, fast_ptr = head->next->next;
    while (fast_ptr) {
        slow_ptr = slow_ptr->next;
        if (fast_ptr->next)
            fast_ptr = fast_ptr->next;
        else
            return slow_ptr;
        if (fast_ptr->next)
            fast_ptr = fast_ptr->next;
        else
            return slow_ptr->next;
    }
    return NULL;
}

int main() {
    return 0;
}
