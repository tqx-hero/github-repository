//
// Created by Administrator on 2026/7/2.
//

#include "ListNode.h"

ListNode::ListNode() : val(0), next(nullptr) {
}

ListNode::ListNode(int val) : val(val), next(nullptr) {
}

ListNode::ListNode(int val, LIST_PTR next) : val(val), next(next) {
}

ListNode::~ListNode() {
    this->next = nullptr;
}
