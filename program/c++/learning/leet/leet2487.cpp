//
// Created by Administrator on 2026/7/10.
//
/**
* 487. 从链表中移除节点
中等
相关标签
premium lock icon
相关企业
提示
给你一个链表的头节点 head 。

移除每个右侧有一个更大数值的节点。

返回修改后链表的头节点 head 。



示例 1：



输入：head = [5,2,13,3,8]
输出：[13,8]
解释：需要移除的节点是 5 ，2 和 3 。
- 节点 13 在节点 5 右侧。
- 节点 13 在节点 2 右侧。
- 节点 8 在节点 3 右侧。
示例 2：

输入：head = [1,1,1,1]
输出：[1,1,1,1]
解释：每个节点的值都是 1 ，所以没有需要移除的节点。


提示：

给定列表中的节点数目在范围 [1, 105] 内
1 <= Node.val <= 105
 * @return
 */
#include <iostream>
#include "../link/ListNode.h"
#include <vector>
using namespace std;


class Solution {
public:
    void destructor_next(ListNode *cur) {
        while (cur) {
            ListNode *next = cur->next;
            delete cur;
            cur = next;
        }
    }

    //直接申请数组来实现栈，注意delete时必须是delete[]
    ListNode *removeNodes(ListNode *head) {
        if (!head->next)
            return head;
        int *stack = new int[100001], size = 0;
        ListNode *cur = head;
        while (cur) {
            int val = cur->val;
            while (size && stack[size - 1] < val)
                size--;
            stack[size++] = val;
            cur = cur->next;
        }
        cur = head;
        for (int i = 0; i < size - 1; i++) {
            cur->val = stack[i];
            cur = cur->next;
        }
        cur->val = stack[size - 1];
        destructor_next(cur->next);
        cur->next = nullptr;
        delete[] stack;
        return head;
    }

    //用vector模拟栈实现
    // ListNode *removeNodes(ListNode *head) {
    //     if (!head->next)
    //         return head;
    //     vector<int> remains;
    //     ListNode *cur = head;
    //     while (cur) {
    //         //栈不为空并且栈顶小于当前元素，持续弹栈
    //         //直到栈顶大于当前元素，或者栈为空
    //         int value = cur->val;
    //         while (!remains.empty() && remains.back() < value)
    //             remains.pop_back();
    //         remains.push_back(value);
    //         cur = cur->next;
    //     }
    //     //栈不为空，则开始给链表赋值
    //     cur = head;
    //     int last = remains.size() - 1;
    //     for (int i = 0; i < last; i++) {
    //         cur->val = remains.at(i);
    //         cur = cur->next;
    //     }
    //     cur->val = remains.at(last);
    //     destructor_next(cur->next);
    //     cur->next = nullptr;
    //     return head;
    // }
};
//
// int main() {
//     return 0;
// }
