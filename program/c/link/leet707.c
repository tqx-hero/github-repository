//
// Created by Administrator on 2026/6/25.
//
/**
* 707. 设计链表
中等
相关标签
premium lock icon
相关企业
你可以选择使用单链表或者双链表，设计并实现自己的链表。

单链表中的节点应该具备两个属性：val 和 next 。val 是当前节点的值，next 是指向下一个节点的指针/引用。

如果是双向链表，则还需要属性 prev 以指示链表中的上一个节点。假设链表中的所有节点下标从 0 开始。

实现 MyLinkedList 类：

MyLinkedList() 初始化 MyLinkedList 对象。
int get(int index) 获取链表中下标为 index 的节点的值。如果下标无效，则返回 -1 。
void addAtHead(int val) 将一个值为 val 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
void addAtTail(int val) 将一个值为 val 的节点追加到链表中作为链表的最后一个元素。
void addAtIndex(int index, int val) 将一个值为 val 的节点插入到链表中下标为 index 的节点之前。如果 index 等于链表的长度，那么该节点会被追加到链表的末尾。如果 index 比长度更大，该节点将 不会插入 到链表中。
void deleteAtIndex(int index) 如果下标有效，则删除链表中下标为 index 的节点。


示例：

输入
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
输出
[null, null, null, null, 2, null, 3]

解释
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
myLinkedList.get(1);              // 返回 2
myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
myLinkedList.get(1);              // 返回 3


提示：

0 <= index, val <= 1000
请不要使用内置的 LinkedList 库。
调用 get、addAtHead、addAtTail、addAtIndex 和 deleteAtIndex 的次数不超过 2000 。
 * @return
 */
//需要设计一个双向链表，并且结构体内保存链表的头节点、尾节点
//因为要按索引操作链表，所以还需要一个size来记录链表的长度
//当对链表的某个index进行操作时，先判断index靠近哪一边：0还是size-1，然后在靠近那一边作为起始位置
//进行遍历查找

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MyDLinkedNode {
    int val;
    struct MyDLinkedNode *prev, *next;
} MyDLinkedNode;

typedef struct {
    int size;
    //头尾节点指向2个哨兵节点
    MyDLinkedNode *head, *tail;
} MyLinkedList;

MyDLinkedNode *mallocNode(int val) {
    MyDLinkedNode *node = malloc(sizeof(MyDLinkedNode));
    if (!node) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    node->next = node->prev = NULL;
    node->val = val;
    return node;
}

MyLinkedList *myLinkedListCreate() {
    MyLinkedList *list = malloc(sizeof(MyLinkedList));
    MyDLinkedNode *head_sentinel = mallocNode(-1);
    MyDLinkedNode *tail_sentinel = mallocNode(-1);
    if (!list || !head_sentinel || !tail_sentinel) {
        printf("%s\n", strerror(errno));
        free(list);
        free(head_sentinel);
        free(tail_sentinel);
        list = NULL;
        head_sentinel = tail_sentinel = NULL;
        return NULL;
    }
    head_sentinel->next = tail_sentinel;
    tail_sentinel->prev = head_sentinel;
    list->size = 0;
    list->head = head_sentinel;
    list->tail = tail_sentinel;
    return list;
}

MyDLinkedNode *findCurrentNode(MyLinkedList *obj, int index) {
    //比较index与0，size-1的差，哪个差小从哪个地方遍历
    int end = obj->size - 1, i = 0;
    //如果index靠近尾节点，那就从尾节点往前遍历
    MyDLinkedNode *cur;
    if (end - index < index) {
        cur = obj->tail->prev;
        for (i = end; i != index; i--)
            cur = cur->prev;
    }
    //从头节点往后遍历
    else {
        cur = obj->head->next;
        for (i = 0; i != index; i++)
            cur = cur->next;
    }
    return cur;
}

int myLinkedListGet(MyLinkedList *obj, int index) {
    if (index < 0 || index >= obj->size)
        return -1;
    return findCurrentNode(obj, index)->val;
}


void myLinkedListAddAtIndex(MyLinkedList *obj, int index, int val) {
    if (index < 0 || index > obj->size)
        return;
    MyDLinkedNode *node = mallocNode(val);
    if (!node) {
        return;
    }
    MyDLinkedNode *cur;
    if (index == obj->size)
        cur = obj->tail;
    else
        //找到当前index节点
        cur = findCurrentNode(obj, index);
    cur->prev->next = node;
    node->prev = cur->prev;
    cur->prev = node;
    node->next = cur;
    obj->size++;
}

void myLinkedListAddAtHead(MyLinkedList *obj, int val) {
    myLinkedListAddAtIndex(obj, 0, val);
}

void myLinkedListAddAtTail(MyLinkedList *obj, int val) {
    myLinkedListAddAtIndex(obj, obj->size, val);
}

void myLinkedListDeleteAtIndex(MyLinkedList *obj, int index) {
    if (index < 0 || index >= obj->size)
        return;
    MyDLinkedNode *cur = findCurrentNode(obj, index);
    cur->prev->next = cur->next;
    cur->next->prev = cur->prev;
    cur->prev = NULL;
    cur->next = NULL;
    free(cur);
    obj->size--;
}

void myLinkedListFree(MyLinkedList *obj) {
    MyDLinkedNode *head = obj->head;
    MyDLinkedNode *cur = head->next;
    MyDLinkedNode *tail = obj->tail;
    while (cur != tail) {
        MyDLinkedNode *next = cur->next;
        cur->next = NULL;
        next->prev = NULL;
        free(cur);
        cur = next;
    }
    head->next = NULL;
    free(obj->head);
    head = NULL;
    tail->prev = NULL;
    free(obj->tail);
    cur = tail = NULL;
    free(obj);
}

/*"MyLinkedList","addAtHead","addAtHead","addAtTail","addAtIndex","get","get","addAtTail","addAtIndex","addAtTail","addAtHead","addAtTail"]
[       [],         [0],        [3],        [5],        [2,3],      [1],  [1],      [2],        [2,3],      [5],        [6],    [3]]*/
int main() {
    MyLinkedList *list = myLinkedListCreate();
    myLinkedListAddAtHead(list, 0);
    myLinkedListAddAtHead(list, 3);
    myLinkedListAddAtTail(list, 5);
    myLinkedListAddAtIndex(list, 2, 3);
    printf("%d\n", myLinkedListGet(list, 1));
    printf("%d\n", myLinkedListGet(list, 1));
    myLinkedListAddAtTail(list, 2);
    myLinkedListAddAtIndex(list, 2, 3);
    myLinkedListAddAtTail(list, 5);
    myLinkedListAddAtHead(list, 6);
    myLinkedListAddAtTail(list, 3);

    myLinkedListFree(list);
    return 0;
}
