#include "ListNode.h"
//
// Created by Administrator on 2026/7/3.
//
//翻转链表练手题
class Solution {
public:
    ListNode *reverseList(ListNode *head) {
        LIST_PTR cur = head;
        LIST_PTR prev = nullptr;
        while (cur) {
            LIST_PTR next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};