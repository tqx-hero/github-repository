//
// Created by Administrator on 2026/7/2.
//

#ifndef LN_LISTNODE_H
#define LN_LISTNODE_H
#define LIST_PTR ListNode*

class ListNode {
public:
    int val;
    LIST_PTR next;

    ListNode();

    ListNode(int val);

    ListNode(int val, LIST_PTR next);

    ~ListNode();
};


#endif //LN_LISTNODE_H
