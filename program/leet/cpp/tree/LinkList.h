//
// Created by Administrator on 2026/7/2.
//

#ifndef LN_LINKLIST_H
#define LN_LINKLIST_H
#include "ListNode.h"


class LinkList {
public:
    LinkList();

    ~LinkList();

    void addFirst(LIST_PTR node);
    LIST_PTR getHead();
private:
    LIST_PTR head;
    int size;
};


#endif //LN_LINKLIST_H
