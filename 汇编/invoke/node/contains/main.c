//
// Created by Administrator on 2026/6/6.
//
#include <stdio.h>
#include <stdlib.h>
typedef struct Node {
    int data;
    struct Node *next;
} Node;

extern int asm_list_find(Node *head, int target);

int main() {
    // 创建链表 1 -> 2 -> 3 -> 4 -> NULL
    Node *head = (Node*)malloc(sizeof(Node));
    head->data = 1;
    head->next = (Node*)malloc(sizeof(Node));
    head->next->data = 2;
    head->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->data = 3;
    head->next->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->next->data = 4;
    head->next->next->next->next = NULL;
    printf("%d\n",asm_list_find(head,10));
    return 0;
}