//
// Created by Administrator on 2026/7/5.
//

#include "solution.h"

Node *solution::getNode(Node *head, int index) {
    int i = 0;
    Node *cur = head;
    while (i++ != index)
        cur = cur->next;
    return cur;
}
