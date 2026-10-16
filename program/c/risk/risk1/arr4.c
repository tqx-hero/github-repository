//
// Created by Administrator on 2026/6/21.
//
/**
*
代码
测试用例
测试用例
测试结果
Q1. 错误的集合
简单
相关标签
premium lock icon
相关企业
集合 s 包含从 1 到 n 的整数。不幸的是，因为数据错误，导致集合里面某一个数字复制成了集合里面的另外一个数字的值，导致集合 丢失了一个数字 并且 有一个数字重复 。

给定一个数组 nums 代表了该集合发生错误后的结果。

请你找出重复出现的整数，再找到丢失的整数，将它们以数组的形式返回。



示例 1：

输入：nums = [1,2,2,4]
输出：[2,3]
示例 2：

输入：nums = [1,1]
输出：[1,2]


提示：

2 <= nums.length <= 104
1 <= nums[i] <= 104
 * @return
 */

#include <stdio.h>
#include <stdlib.h>

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

int *findErrorNums(int *nums, int numsSize, int *returnSize) {
    *returnSize = 2;
    int *ans = malloc(*returnSize * sizeof(int));
    hashInit();
    int i = 0, repeated, lose;
    for (; i < numsSize; i++) {
        int cur = nums[i];
        if (hashGet(cur) != -1)
            repeated = cur;
        else
            hashPut(cur, 0);
    }
    for (i = 1; i <= numsSize && hashGet(i) != -1; i++);
    lose = i;
    ans[0] = repeated;
    ans[1] = lose;
    hashFree();
    return ans;
}

//通过异或运算来找到重复元素与缺失元素，空间复杂度O(1)，时间复杂度O(n)
int *findErrorNumsByXor(int *nums, int numsSize, int *returnSize) {
    *returnSize = 2;
    int *ans = malloc(*returnSize * sizeof(int));
    int i = 0, xor_val = 0;
    for (; i < numsSize; i++) {
        //将数组内各元素和1~n全部做异或运算
        //由于没有重复也不缺失的元素在两个序列中都会出现一次，异或运算会将它们抵消
        //所以最终的运算结果是重复的那个元素^缺失的那个元素(重复元素出现3次，缺失元素出现1次)
        xor_val ^= nums[i];
        xor_val ^= (i + 1);
    }
    //由于2个元素不相等，所以异或结果一定不为0，取最右边的那个1位置来区分这两个元素
    int mask = xor_val & -xor_val, group1 = 0, group2 = 0;
    //分别以这个1位置为界，区分成2组值，(即这一位是1的与是0的，通过与运算来判断)再分别做一次异或运算。
    //这样，同样是在1~n与数组中出现过一次的值不管怎么分组都会抵消，剩余的就是这两个元
    //素，这样就区分出他俩来。接下来就是如何判定哪个是缺失的数，哪个是重复数据，只需要遍历一遍数组即可
    for (i = 0; i < numsSize; i++) {
        //与掩码异或不为0的分成一组
        if (nums[i] & mask)
            group1 ^= nums[i];
        else
            group2 ^= nums[i];

        if ((i + 1) & mask)
            group1 ^= (i + 1);
        else
            group2 ^= (i + 1);
    }
    int lose, repeat;
    //区分出两个数据group1与group2之后，就需要再次遍历数组，找到出现的那个元素，就是重复元素，另一个则是缺失元素
    for (i = 0; i < numsSize; i++) {
        if (nums[i] == group1) {
            repeat = group1;
            lose = group2;
            break;
        }
        if (nums[i] == group2) {
            repeat = group2;
            lose = group1;
            break;
        }
    }
    ans[0] = repeat;
    ans[1] = lose;
    return ans;
}

int main() {
    int arr[] = {3, 2, 3, 4, 6, 5}, size;
    // int arr[] = {1, 2, 2, 4}, size;
    int *ans = findErrorNumsByXor(arr, sizeof(arr) / sizeof(int), &size);
    // int *ans = findErrorNums(arr, sizeof(arr) / sizeof(int), &size);
    for (int i = 0; i < size; ++i) {
        printf("%d ", ans[i]);
    }
    free(ans);
    return 0;
}
