//
// Created by Administrator on 2026/4/25.
//
#include "stack.h"

#include <stdlib.h>


Stack *init(int size) {
    Stack *stack = malloc(sizeof(Stack) + size * sizeof(int));
    stack->ptr = -1;
    stack->size = size;
    return stack;
}

void push(STACKPTR(this), int x) {
    this->arr[++this->ptr] = x;
}

_Bool isEmpty(STACKPTR(this)) {
    return this->ptr == -1;
}

int pop(STACKPTR(this)) {
    return this->arr[this->ptr--];
}


int peek(STACKPTR(this)) {
    return this->arr[this->ptr];
}

void free_stack(STACKPTR(this)) {
    free(this);
}

// void init(STACKPTR(this)) {
//     this->ptr = -1;
// }
//
// void push(STACKPTR(this), VOID x) {
//     this->arr[++this->ptr] = x;
// }
//
// _Bool isEmpty(STACKPTR(this)) {
//     return this->ptr == -1;
// }
//
// VOID pop(STACKPTR(this)) {
//     return this->arr[this->ptr--];
// }
//
//
// VOID peek(STACKPTR(this)) {
//     return this->arr[this->ptr];
// }
