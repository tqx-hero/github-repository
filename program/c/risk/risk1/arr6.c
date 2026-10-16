//
// Created by Administrator on 2026/6/22.
//
/**
* Q3. 找到所有数组中消失的数字
简单
相关标签
premium lock icon
相关企业
提示
给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。



示例 1：

输入：nums = [4,3,2,7,8,2,3,1]
输出：[5,6]
示例 2：

输入：nums = [1,1]
输出：[2]


提示：

n == nums.length
1 <= n <= 105
1 <= nums[i] <= n
进阶：你能在不使用额外空间且时间复杂度为 O(n) 的情况下解决这个问题吗? 你可以假定返回的数组不算在额外空间内。
 * @return
 */

#define HASH_SIZE 1009   // 质数，减少冲突
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

int *findDisappearedNumbers(int *nums, int numsSize, int *returnSize) {
    hashInit();
    int i = 0;
    for (; i < numsSize; i++)
        hashPut(nums[i], 0);
    int *ans = calloc(numsSize, sizeof(int));
    int count = 0;
    for (i = 1; i <= numsSize; i++) {
        if (hashGet(i) == -1)
            ans[count++] = i;
    }
    *returnSize = count;
    hashFree();
    return ans;
}

int main() {
    int arr[] = {4, 3, 2, 7, 8, 2, 3, 1}, size;
    int *ans = findDisappearedNumbers(arr, sizeof(arr) / sizeof(int), &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", ans[i]);
    }
    free(ans);
    return 0;
}
