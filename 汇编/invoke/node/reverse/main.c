#include <stdio.h>
#include <stdlib.h>

// 定义链表节点
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 汇编函数：反转链表，返回新头结点
extern Node* asm_reverse_list(Node *head);

// 打印链表
void print_list(Node *head) {
    while(head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

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

    printf("原链表：");
    print_list(head);

    // 调用汇编反转
    Node *new_head = asm_reverse_list(head);

    printf("反转后：");
    print_list(new_head); // 输出 4 3 2 1

    return 0;
}