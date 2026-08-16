//
// Created by Administrator on 2026/7/5.
//

#include "node.h"

Node::Node(int value) : value(value), next(nullptr) {
    cout << "Init a new node with value " << value << endl;
}

Node::~Node() {
}
