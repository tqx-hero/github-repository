//
// Created by Administrator on 2026/6/5.
//
/**
* 503. 下一个更大元素 II
中等
相关标签
premium lock icon
相关企业
给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回 nums 中每个元素的 下一个更大元素 。

数字 x 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 。



示例 1:

输入: nums = [1,2,1]
输出: [2,-1,2]
解释: 第一个 1 的下一个更大的数是 2；
数字 2 找不到下一个更大的数；
第二个 1 的下一个最大的数需要循环搜索，结果也是 2。
示例 2:

输入: nums = [1,2,3,4,3]
输出: [2,3,4,-1,4]


提示:

1 <= nums.length <= 104
-109 <= nums[i] <= 109
 */
#define HASH_SIZE 1009   // 质数，减少冲突
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// 哈希结点
typedef struct HashNode {
    int key;
    int val;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[HASH_SIZE];
// 哈希映射函数
static int hashFunc(int key) {
    return abs(key) % HASH_SIZE;
}

// 初始化哈希表
void hashInit() {
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i] = NULL;
}

// 插入/更新
void hashPut(int key, int val) {
    int idx = hashFunc(key);
    HashNode *cur = hashTable[idx];
    // 存在则更新
    while (cur) {
        if (cur->key == key) {
            cur->val = val;
            return;
        }
        cur = cur->next;
    }
    // 头插新建结点
    HashNode *newNode = (HashNode *) malloc(sizeof(HashNode));
    newNode->key = key;
    newNode->val = val;
    newNode->next = hashTable[idx];
    hashTable[idx] = newNode;
}

// 查找，不存在返回-1
int hashGet(int key) {
    int idx = hashFunc(key);
    HashNode *cur = hashTable[idx];
    while (cur) {
        if (cur->key == key)
            return cur->val;
        cur = cur->next;
    }
    return -1;
}

// 删除键
void hashRemove(int key) {
    int idx = hashFunc(key);
    HashNode **p = &hashTable[idx];
    while (*p) {
        if ((*p)->key == key) {
            HashNode *del = *p;
            *p = (*p)->next;
            free(del);
            return;
        }
        p = &(*p)->next;
    }
}

// 释放整张哈希表
void hashFree() {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *cur = hashTable[i];
        while (cur) {
            HashNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
}

#define STACK_MAX_SIZE 100001

//
typedef struct Stack {
    int arr[STACK_MAX_SIZE];
    int count;
    int ptr;
} Stack;

void init(Stack *this) {
    this->count = 0;
    this->ptr = -1;
}

int push(Stack *this, int x) {
    if (this->count >= STACK_MAX_SIZE)
        return -1;
    this->arr[++this->ptr] = x;
    this->count++;
    return 0;
}

int pop(Stack *this) {
    if (this->count == 0)
        return -1;
    this->count--;
    return this->arr[this->ptr--];
}

_Bool isEmpty(Stack *this) {
    return this->count == 0;
}

int peek(Stack *this) {
    if (this->count == 0)
        return -1;
    return this->arr[this->ptr];
}

int *nextGreaterElements(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize;
    int *arr = malloc(numsSize * sizeof(int));
    if (numsSize == 1) {
        *arr = -1;
        return arr;
    }
    hashInit();
    //由于是循环查找
    //所以应该先从倒数第二个数字开始往前先遍历一边，把所有前面的情况先压入栈内
    //然后再从倒数第一个数字重新开始统计，查看栈内情况
    Stack stack = {};
    init(&stack);
    int i = numsSize - 2;
    for (; i >= 0; --i) {
        int num = *(nums + i);
        //栈为空或者栈顶元素比自身大，直接压栈
        //否则将栈顶元素弹出，直到找到比自身大或者栈空为止，入栈
        //此次只压栈，不入哈希表
        while (!isEmpty(&stack) && peek(&stack) <= num)
            pop(&stack);
        push(&stack, num);
    }
    //从后往前开始遍历，比较栈顶元素，按情况入hash表
    for (i = numsSize - 1; i >= 0; --i) {
        int num = *(nums + i);
        int top = -1;
        while (!isEmpty(&stack) && (top = peek(&stack)) <= num)
            pop(&stack);
        if (isEmpty(&stack))
            hashPut(i, -1);
        else
            hashPut(i, top);
        push(&stack, num);
    }
    //统计哈希表结果
    for (i = 0; i < numsSize; ++i)
        *(arr + i) = hashGet(i);
    hashFree();
    return arr;
}

// int main() {
//     // int arr[]= {1,2,3,4,3};
//     int arr[]= {100,1,11,1,120,111,123,1,-1,-100};
//     int size ;
//     int * res = nextGreaterElements(arr,10,&size);
//     for (int i = 0; i < size; ++i)
//         printf("%d ",*(res+i));
//     free(res);
//     return 0;
// }
//[120,11,120,120,123,123,-1,100,100,100]