//
// Created by Administrator on 2026/6/13.
//
/**
 *
 * @return
 */

#include <stdlib.h>

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

typedef struct Node Node;

#define MAX_SIZE 4096

//定义一个循环队列
typedef struct ArrayDeque {
    Node *obj[MAX_SIZE];
    int count;
    int front;
    int rear;
} ArrayDeque;

_Bool isEmpty(ArrayDeque *queue) {
    return queue->count == 0;
}

void initQueue(ArrayDeque *queue) {
    queue->count = 0;
    queue->rear = 0;
    queue->front = 0;
}

Node *poll(ArrayDeque *queue) {
    if (!isEmpty(queue)) {
        Node *obj = queue->obj[queue->front];
        queue->count--;
        queue->front = (queue->front + 1) & (MAX_SIZE - 1);
        return obj;
    }
    return NULL;
}

Node *peek(ArrayDeque *queue) {
    if (!isEmpty(queue))
        return queue->obj[queue->front];
    return NULL;
}

_Bool isFull(ArrayDeque *queue) {
    return queue->count == MAX_SIZE;
}

int size(ArrayDeque *queue) {
    return queue->count;
}

int offer(ArrayDeque *queue, Node *obj) {
    if (!isFull(queue)) {
        queue->obj[queue->rear] = obj;
        queue->rear = (queue->rear + 1) & (MAX_SIZE - 1);
        queue->count++;
        return 1;
    }
    return 0;
}

struct Node *connect(struct Node *root) {
    if (!root)
        return NULL;
    ArrayDeque queue = {};
    initQueue(&queue);
    offer(&queue, root);
    while (!isEmpty(&queue)) {
        Node *rt = poll(&queue);
        Node *cur = rt;
        while (!isEmpty(&queue)) {
            cur->next = poll(&queue);
            cur = cur->next;
        }
        //将rt这个next链表上所有不为null的节点入队列
        while (rt) {
            if (rt->left)
                offer(&queue, rt->left);
            if (rt->right)
                offer(&queue, rt->right);
            rt = rt->next;
        }
    }
    return root;
}

int main() {
    Node n7 = {7,NULL,NULL,NULL};
    Node n5 = {5,NULL,NULL,NULL};
    Node n4 = {4,NULL,NULL,NULL};
    Node n3 = {3,NULL, &n7,NULL};
    Node n2 = {2, &n4, &n5,NULL};
    Node n1 = {1, &n2, &n3,NULL};
    Node *ret = connect(&n1);
    return 0;
}
