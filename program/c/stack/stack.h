//
// Created by Administrator on 2026/4/25.
//

// #ifndef CLONWORKSPACE_STACK_H
#define CLONWORKSPACE_STACK_H
#define STACKPTR(name) Stack* name
//
// typedef struct Stack {
//     VOID arr[STACK_MAX_SIZE];
//     int ptr;
//     //可选函数指针
//     VOID (*func_ptr)(VOID, ...);
// } Stack;

typedef struct Stack {
    int ptr, size;
    int arr[];
    //可选函数指针
    // VOID (*func_ptr)(VOID, ...);
} Stack;

Stack *init(int size);

void push(STACKPTR(this), int x);

_Bool isEmpty(STACKPTR(this)) {
    return this->ptr == -1;
}

int pop(STACKPTR(this));


int peek(STACKPTR(this));

void free_stack(STACKPTR(this));

// #endif //CLONWORKSPACE_STACK_H
// void init(STACKPTR(this));
//
// //往栈内放元素
// void push(STACKPTR(this), VOID x);
//
// _Bool isEmpty(STACKPTR(this));
//
// //出栈
// VOID pop(STACKPTR(this));
//
// //查看栈顶元素
// VOID peek(STACKPTR(this));
