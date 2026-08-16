//
// Created by Administrator on 2026/6/6.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

extern Node *asm_list_merge(Node *h1, Node *h2);

// 打印链表
void print_list(Node *head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

int main() {
    // 创建链表 1 -> 2 -> 3 -> 4 -> NULL
    Node *head = (Node *) malloc(sizeof(Node));
    head->data = 1;
    head->next = (Node *) malloc(sizeof(Node));
    head->next->data = 10;
    head->next->next = (Node *) malloc(sizeof(Node));
    head->next->next->data = 20;
    head->next->next->next = (Node *) malloc(sizeof(Node));
    head->next->next->next->data = 30;
    head->next->next->next->next = NULL;

    // 创建链表 1 -> 2 -> 3 -> 4 -> NULL
    Node *head1 = (Node *) malloc(sizeof(Node));
    head1->data = 5;
    head1->next = (Node *) malloc(sizeof(Node));
    head1->next->data = 6;
    head1->next->next = (Node *) malloc(sizeof(Node));
    head1->next->next->data = 7;
    head1->next->next->next = (Node *) malloc(sizeof(Node));
    head1->next->next->next->data = 16;
    head1->next->next->next->next = NULL;
    print_list(asm_list_merge(head, head1));
    return 0;
}
