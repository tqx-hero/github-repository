//
// Created by Administrator on 2026/6/5.
//
/**
*
代码
测试用例
测试用例
测试结果
173. 二叉搜索树迭代器
中等
相关标签
premium lock icon
相关企业
实现一个二叉搜索树迭代器类BSTIterator ，表示一个按中序遍历二叉搜索树（BST）的迭代器：
BSTIterator(TreeNode root) 初始化 BSTIterator 类的一个对象。BST 的根节点 root 会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST 中的数字，且该数字小于 BST 中的任何元素。
boolean hasNext() 如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。
int next()将指针向右移动，然后返回指针处的数字。
注意，指针初始化为一个不存在于 BST 中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。

你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 的中序遍历中至少存在一个下一个数字。



示例：


输入
["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next", "hasNext", "next", "hasNext"]
[[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
输出
[null, 3, 7, true, 9, true, 15, true, 20, false]

解释
BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
bSTIterator.next();    // 返回 3
bSTIterator.next();    // 返回 7
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 9
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 15
bSTIterator.hasNext(); // 返回 True
bSTIterator.next();    // 返回 20
bSTIterator.hasNext(); // 返回 False


提示：

树中节点的数目在范围 [1, 105] 内
0 <= Node.val <= 106
最多调用 105 次 hasNext 和 next 操作


进阶：

你可以设计一个满足下述条件的解决方案吗？next() 和 hasNext() 操作均摊时间复杂度为 O(1) ，并使用 O(h) 内存。其中 h 是树的高度。
宗旨就是中序遍历，先把所有左子树压栈
当调用next方法取数时，弹栈，并把栈顶结点的右子树的在全部压一边栈
这样的惰性压栈就达到了仅使用O(h)的空间，且均摊时间复杂度为O(1)
 * @return
 */
// #include "stack.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../node/treenode.h"
#define STACK_MAX_SIZE 32
//
#define TREENODE struct TreeNode*
typedef struct TreeNode TreeNode;

typedef struct Stack {
    TREENODE arr[STACK_MAX_SIZE];
    int ptr;
} Stack;

typedef struct {
    Stack stack;
} BSTIterator;

#define BSTPTR BSTIterator*


void init(Stack *this) {
    this->ptr = -1;
}

int push(Stack *this, TREENODE x) {
    if (this->ptr + 1 == STACK_MAX_SIZE)
        return -1;
    this->arr[++this->ptr] = x;
    return 0;
}

_Bool isEmpty(Stack *this) {
    return this->ptr == -1;
}

TREENODE pop(Stack *this) {
    if (isEmpty(this))
        return NULL;
    return this->arr[this->ptr--];
}


//压入左子树
void push_tree(BSTPTR bst_iterator,TREENODE node) {
    if (!node)
        return;
    push(&bst_iterator->stack, node);
    push_tree(bst_iterator, node->left);
}

BSTIterator *bSTIteratorCreate(struct TreeNode *root) {
    BSTPTR bst_iterator = malloc(sizeof(BSTIterator));
    init(&bst_iterator->stack);
    //将左子树全部压栈
    push_tree(bst_iterator, root);
    return bst_iterator;
}

int bSTIteratorNext(BSTIterator *obj) {
    //弹栈获取当前节点
    TREENODE tree_node = pop(&obj->stack);
    push_tree(obj, tree_node->right);
    return tree_node->val;
}

bool bSTIteratorHasNext(BSTIterator *obj) {
    return !isEmpty(&obj->stack);
}

void bSTIteratorFree(BSTIterator *obj) {
    free(obj);
    obj = NULL;
}

#define MAKE_FUN(type_a,a,type_b,b)  type_a a(type_b b)\
    { \
        return b;  \
    }

MAKE_FUN(int,hello,int,number)



// int main() {
//     // TreeNode t5 = {20,NULL,NULL};
//     // TreeNode t4 = {9,NULL,NULL};
//     // TreeNode t3 = {15, &t4, &t5};
//     // TreeNode t2 = {3,NULL,NULL};
//     // TreeNode t1 = {7, &t2, &t3};
//     // BSTPTR bst_iterator = bSTIteratorCreate(&t1);
//     // while (bSTIteratorHasNext(bst_iterator)) {
//     //     printf("%d ", bSTIteratorNext(bst_iterator));
//     // }
//     // bSTIteratorFree(bst_iterator);
//     // char buf[200];
//     // scanf("%s",buf);
//     // printf("%s\n",buf);
//
//     printf("%d\n",hello(100));
//
//     return 0;
// }
