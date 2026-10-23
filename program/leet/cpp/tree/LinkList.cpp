//
// Created by Administrator on 2026/7/2.
//

#include "LinkList.h"

LinkList::LinkList() : head(new ListNode(-1, nullptr)), size(0) {
}

LinkList::~LinkList() {
    LIST_PTR cur = this->head;
    while (cur) {
        LIST_PTR tmp = cur->next;
        delete cur;
        cur = tmp;
    }
    this->head = nullptr;
}

void LinkList::addFirst(ListNode *node) {
    node->next = this->head->next;
    this->head->next = node;
    this->size++;
}

ListNode *LinkList::getHead() {
    return this->head->next;
}
