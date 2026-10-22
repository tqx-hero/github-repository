#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
// Created by Administrator on 2026/6/30.
//
/**
* 1670. 设计前中后队列
中等
相关标签
premium lock icon
相关企业
提示
请你设计一个队列，支持在前，中，后三个位置的 push 和 pop 操作。

请你完成 FrontMiddleBack 类：

FrontMiddleBack() 初始化队列。
void pushFront(int val) 将 val 添加到队列的 最前面 。
void pushMiddle(int val) 将 val 添加到队列的 正中间 。
void pushBack(int val) 将 val 添加到队里的 最后面 。
int popFront() 将 最前面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
int popMiddle() 将 正中间 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
int popBack() 将 最后面 的元素从队列中删除并返回值，如果删除之前队列为空，那么返回 -1 。
请注意当有 两个 中间位置的时候，选择靠前面的位置进行操作。比方说：

将 6 添加到 [1, 2, 3, 4, 5] 的中间位置，结果数组为 [1, 2, 6, 3, 4, 5] 。
从 [1, 2, 3, 4, 5, 6] 的中间位置弹出元素，返回 3 ，数组变为 [1, 2, 4, 5, 6] 。


示例 1：

输入：
["FrontMiddleBackQueue", "pushFront", "pushBack", "pushMiddle", "pushMiddle", "popFront", "popMiddle", "popMiddle", "popBack", "popFront"]
[[], [1], [2], [3], [4], [], [], [], [], []]
输出：
[null, null, null, null, null, 1, 3, 4, 2, -1]

解释：
FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [1]
q.pushBack(2);    // [1, 2]
q.pushMiddle(3);  // [1, 3, 2]
q.pushMiddle(4);  // [1, 4, 3, 2]
q.popFront();     // 返回 1 -> [4, 3, 2]
q.popMiddle();    // 返回 3 -> [4, 2]
q.popMiddle();    // 返回 4 -> [2]
q.popBack();      // 返回 2 -> []
q.popFront();     // 返回 -1 -> [] （队列为空）


提示：

1 <= val <= 109
最多调用 1000 次 pushFront， pushMiddle， pushBack， popFront， popMiddle 和 popBack 。
 * @return
 */

#define OP_ADD 0
#define OP_DEL 1
#define POS_HEAD 0
#define POS_MID 1
#define POS_TAIL 2

typedef struct QDLinkNode {
    int value;
    struct QDLinkNode *prev, *next;
} QDLinkNode;

typedef struct {
    int size, middle_index;
    QDLinkNode *head, *middle, *tail;
} FrontMiddleBackQueue;

QDLinkNode *malloc_node(int val) {
    QDLinkNode *node = malloc(sizeof(QDLinkNode));
    if (!node) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    node->prev = node->next = NULL;
    node->value = val;
    return node;
}

FrontMiddleBackQueue *frontMiddleBackQueueCreate() {
    QDLinkNode *head = malloc_node(-1);
    QDLinkNode *tail = malloc_node(-1);
    FrontMiddleBackQueue *queue = malloc(sizeof(FrontMiddleBackQueue));
    if (!head || !tail || !queue) {
        printf("%s\n", strerror(errno));
        queue = NULL;
        head = tail = NULL;
        return NULL;
    }
    head->next = tail;
    tail->prev = head;
    queue->size = 0;
    queue->middle_index = -1;
    queue->head = head;
    queue->tail = tail;
    queue->middle = NULL;
    return queue;
}

void balance_middle(FrontMiddleBackQueue *obj) {
    int cur_mid = (obj->size - 1) >> 1;
    //真实的中间节点靠前，指针前移
    while (cur_mid < obj->middle_index) {
        obj->middle = obj->middle->prev;
        obj->middle_index--;
    }
    while (cur_mid > obj->middle_index) {
        obj->middle = obj->middle->next;
        obj->middle_index++;
    }
}

//position: 0:头部;1:中部;2:尾部;
void after_create(FrontMiddleBackQueue *obj, int position) {
    if (position < POS_TAIL)
        obj->middle_index++;
    balance_middle(obj);
}

void after_delete(FrontMiddleBackQueue *obj, int position) {
    if (position < POS_TAIL)
        obj->middle_index--;
    balance_middle(obj);
}

//operation : 0:新建
//1:删除
void update_middle(FrontMiddleBackQueue *obj, int operation, int position) {
    //说明刚新建节点还没设置中间索引的指针，分配
    if (obj->size == 0) {
        obj->middle_index = -1;
        obj->middle = NULL;
    } else if (obj->middle_index == -1) {
        obj->middle = obj->head->next;
        obj->middle_index = 0;
    } else {
        //链表不为空，则查看当前操作operation
        switch (operation) {
            case 0:
                after_create(obj, position);
                break;
            case 1:
                after_delete(obj, position);
                break;
            default: break;
        }
    }
}

//在cur前面添加node
void add_node_before_cur(QDLinkNode *node, QDLinkNode *cur) {
    QDLinkNode *prev = cur->prev;
    cur->prev = node;
    node->next = cur;
    if (prev) {
        prev->next = node;
        node->prev = prev;
    } else
        node->prev = NULL;
}

//在cur后面添加node
void add_node_after_cur(QDLinkNode *node, QDLinkNode *cur) {
    QDLinkNode *next = cur->next;
    cur->next = node;
    node->prev = cur;
    if (next) {
        next->prev = node;
        node->next = next;
    } else
        node->next = NULL;
}

void delete_node(FrontMiddleBackQueue *obj, QDLinkNode *node) {
    if (node == obj->middle)
        obj->middle = node->prev;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    node->prev = NULL;
    node->next = NULL;
    free(node);
}

void frontMiddleBackQueuePushFront(FrontMiddleBackQueue *obj, int val) {
    QDLinkNode *node = malloc_node(val);
    if (!node)
        return;
    add_node_before_cur(node, obj->head->next);
    obj->size++;
    update_middle(obj, OP_ADD, POS_HEAD);
}

void frontMiddleBackQueuePushMiddle(FrontMiddleBackQueue *obj, int val) {
    int odd, size = obj->size;
    if (!size) {
        frontMiddleBackQueuePushFront(obj, val);
        return;
    }
    QDLinkNode *node = malloc_node(val);
    if (!node)
        return;
    //判断奇偶性，size是奇数，直接插入，偶数那就需要从middle后面插入

    if ((odd = (size & 1)))
        add_node_before_cur(node, obj->middle);
    else
        add_node_after_cur(node, obj->middle);
    obj->size++;
    update_middle(obj,OP_ADD, odd ? POS_MID : POS_TAIL);
}

void frontMiddleBackQueuePushBack(FrontMiddleBackQueue *obj, int val) {
    int size = obj->size;
    if (!size) {
        frontMiddleBackQueuePushFront(obj, val);
        return;
    }
    QDLinkNode *node = malloc_node(val);
    if (!node)
        return;
    add_node_before_cur(node, obj->tail);
    obj->size++;
    update_middle(obj,OP_ADD,POS_TAIL);
}


bool isEmpty(FrontMiddleBackQueue *obj) {
    return obj->size == 0;
}

int frontMiddleBackQueuePopFront(FrontMiddleBackQueue *obj) {
    if (isEmpty(obj))
        return -1;
    QDLinkNode *node = obj->head->next;
    int ret = node->value;
    delete_node(obj, node);
    obj->size--;
    update_middle(obj,OP_DEL,POS_HEAD);
    return ret;
}

int frontMiddleBackQueuePopMiddle(FrontMiddleBackQueue *obj) {
    if (isEmpty(obj))
        return -1;
    int ret = obj->middle->value;
    delete_node(obj, obj->middle);
    obj->size--;
    update_middle(obj,OP_DEL,POS_MID);
    return ret;
}

int frontMiddleBackQueuePopBack(FrontMiddleBackQueue *obj) {
    if (isEmpty(obj))
        return -1;
    QDLinkNode *tail = obj->tail->prev;
    int ret = tail->value;
    delete_node(obj, tail);
    obj->size--;
    update_middle(obj,OP_DEL,POS_TAIL);
    return ret;
}

void frontMiddleBackQueueFree(FrontMiddleBackQueue *obj) {
    QDLinkNode *cur = obj->head;
    while (cur) {
        QDLinkNode *next = cur->next;
        cur->prev = NULL;
        cur->next = NULL;
        free(cur);
        cur = next;
    }
    free(obj);
}

int main() {
    /*FrontMiddleBackQueue q = new FrontMiddleBackQueue();
q.pushFront(1);   // [
1
]
q.pushBack(2);    // [1,
2
]
q.pushMiddle(3);  // [1,
3
, 2]
q.pushMiddle(4);  // [1,
4
, 3, 2]
q.popFront();     // 返回 1 -> [4, 3, 2]
q.popMiddle();    // 返回 3 -> [4, 2]
q.popMiddle();    // 返回 4 -> [2]
q.popBack();      // 返回 2 -> []
q.popFront();     // 返回 -1 -> [] （队列为空）*/
    FrontMiddleBackQueue *queue = frontMiddleBackQueueCreate();
    // frontMiddleBackQueuePushFront(queue, 1);
    // frontMiddleBackQueuePushBack(queue, 2);
    // frontMiddleBackQueuePushMiddle(queue, 3);
    // frontMiddleBackQueuePushMiddle(queue, 4);
    // printf("%d\n", frontMiddleBackQueuePopFront(queue));
    // printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    // printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    // printf("%d\n", frontMiddleBackQueuePopBack(queue));
    // printf("%d\n", frontMiddleBackQueuePopFront(queue));
    // frontMiddleBackQueueFree(queue);
    /*["FrontMiddleBackQueue","popMiddle","popMiddle","pushMiddle","popBack","popFront","popMiddle"]
￼
[           [],                     [],         [],             [8],    [],         [],     []]*/
    // printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    // printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    // frontMiddleBackQueuePushMiddle(queue, 8);
    // printf("%d\n", frontMiddleBackQueuePopBack(queue));
    // printf("%d\n", frontMiddleBackQueuePopFront(queue));
    // printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    /*["FrontMiddleBackQueue","pushMiddle","popBack","popMiddle","popMiddle","pushBack","pushFront","popFront",
￼
[               [],              [874835],      [],     [],             [],     [319750],   [782168],       [],
*"pushMiddle","pushMiddle","popMiddle","popMiddle","pushMiddle","popMiddle","pushMiddle"]

[16473],        [495349],       [],         [],         [596131],       [],     [583563]]*/
    frontMiddleBackQueuePushMiddle(queue, 874835);
    printf("%d\n", frontMiddleBackQueuePopBack(queue));
    printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    frontMiddleBackQueuePushBack(queue, 319750);
    frontMiddleBackQueuePushFront(queue, 782168);
    printf("%d\n", frontMiddleBackQueuePopFront(queue));
    frontMiddleBackQueuePushMiddle(queue, 16473);
    frontMiddleBackQueuePushMiddle(queue, 495349);
    printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    frontMiddleBackQueuePushMiddle(queue, 596131);
    printf("%d\n", frontMiddleBackQueuePopMiddle(queue));
    frontMiddleBackQueuePushMiddle(queue, 583563);
    frontMiddleBackQueueFree(queue);
    return 0;
}
