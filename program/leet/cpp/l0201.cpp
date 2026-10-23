//
// Created by Administrator on 2026/7/15.
//
/**
* 面试题 02.01. 移除重复节点
简单
相关标签
premium lock icon
相关企业
提示
编写代码，移除未排序链表中的重复节点。保留最开始出现的节点。

示例1：

 输入：[1, 2, 3, 3, 2, 1]
 输出：[1, 2, 3]
示例2：

 输入：[1, 1, 1, 1, 2]
 输出：[1, 2]
提示：

链表长度在[0, 20000]范围内。
链表元素在[0, 20000]范围内。
进阶：

如果不得使用临时缓冲区，该怎么解决？
 * @return
 */
#include "../link/ListNode.h"
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    ListNode *removeDuplicateNodes(ListNode *head) {
        if (!head)
            return head;
        unordered_set<int> set;
        ListNode sentinel(0, head);
        ListNode *cur = head, *prev = &sentinel;
        while (cur) {
            //如果当前节点值存在于哈希表，删除该节点
            if (set.count(cur->val))
                prev->next = cur->next;
            else {
                set.emplace(cur->val);
                prev = prev->next;
            }
            cur = cur->next;
        }
        return sentinel.next;
    }
};

// int main() {
//     return 0;
// }
