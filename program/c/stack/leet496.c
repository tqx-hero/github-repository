//
// Created by Administrator on 2026/6/4.
//
/**
*
代码
测试用例
测试用例
测试结果
496. 下一个更大元素 I
简单
相关标签
premium lock icon
相关企业
nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。

给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0 开始计数，其中nums1 是 nums2 的子集。

对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定 nums2[j] 的 下一个更大元素 。如果不存在下一个更大元素，那么本次查询的答案是 -1 。

返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。



示例 1：

输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
输出：[-1,3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
- 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
- 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
示例 2：

输入：nums1 = [2,4], nums2 = [1,2,3,4].
输出：[3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
- 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。


提示：

1 <= nums1.length <= nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 104
nums1和nums2中所有整数 互不相同
nums1 中的所有整数同样出现在 nums2 中


进阶：你可以设计一个时间复杂度为 O(nums1.length + nums2.length) 的解决方案吗？
 * @return
 */
#include <stdio.h>
#include <stdlib.h>

// #include "../hash/hash.h"
// #include "stack.h"
#define HASH_SIZE 1009   // 质数，减少冲突

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

int findLeastMax(int after, int cur) {
    if (after > cur || after == -1)
        return after;
    return findLeastMax(hashGet(after), cur);
}

//用单调栈实现查找
int *nextGreaterElement(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize) {
    int *res = malloc(nums1Size * sizeof(int));
    *returnSize = nums1Size;
    if (nums2Size == 1) {
        *res = -1;
        return res;
    }
    hashInit();
    int i = nums2Size - 1;
    Stack stack = {};
    init(&stack);
    //倒序遍历，对数据进行压栈
    //单调栈内存放的数据均为当前最近的最大值
    //当元素大于栈顶元素时，就把栈顶弹出去，因为栈顶已经不如当前元素大，那也永远不可能时前面的元素的最近的最大值
    //因为当前元素已经比它大，当前元素应该顶替栈顶位置
    //继续找知道找到比元素大或者栈空。栈空记-1
    //找到大的以后记录最大值，将当前元素压栈保存
    for (; i >= 0; --i) {
        int num = *(nums2 + i);
        //栈空则将其最大值置为-1
        int top=-1;
        while (!isEmpty(&stack) && (top = peek(&stack)) < num)
            //栈顶小于当前元素，将栈顶弹出，继续循环找最大元素
            pop(&stack);
        if (isEmpty(&stack))
            hashPut(num, -1);
        else
            hashPut(num,top);
        //当前元素入栈
        push(&stack, num);
    }
    for (i = 0; i < nums1Size; ++i)
        *(res + i) = hashGet(*(nums1 + i));
    hashFree();
    return res;
}

//用并查集查找
// int *nextGreaterElement(int *nums1, int nums1Size, int *nums2, int nums2Size, int *returnSize) {
//     int *res = malloc(nums1Size * sizeof(int));
//     *returnSize = nums1Size;
//     if (nums2Size == 1) {
//         *res = -1;
//         return res;
//     }
//     hashInit();
//     //倒序遍历，同时记录最大值
//     //初始化末尾数值，值置为-1
//     int i = nums2Size - 1;
//     int max = *(nums2 + i);
//     hashPut(max, -1);
//     for (--i; i >= 0; --i) {
//         int cur = *(nums2 + i);
//         int after = *(nums2 + i + 1);
//         if (cur < after)
//             hashPut(cur, after);
//         else if (cur >max) {
//             max =cur;
//             hashPut(cur,-1);
//         }
//         else
//             hashPut(cur,findLeastMax(after,cur));
//     }
//     for ( i = 0; i < nums1Size; ++i)
//         *(res+i) = hashGet(*(nums1+i));
//     hashFree();
//     return res;
// }


// int main() {
//     int nums1[] = {4, 1, 2}, nums2[] = {1, 3, 4, 2};
//     int size = 0;
//     int *result = nextGreaterElement(nums1, 3, nums2, 4, &size);
//     for (int i = 0; i < size; ++i) {
//         printf("%d ", *(result + i));
//     }
//     free(result);
//     return 0;
// }
