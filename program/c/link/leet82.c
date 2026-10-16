//
// Created by Administrator on 2026/6/1.
//
/**
*
代码
测试用例
测试用例
测试结果
82. 删除排序链表中的重复元素 II
中等
相关标签
premium lock icon
相关企业
给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。



示例 1：


输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]
示例 2：


输入：head = [1,1,1,2,3]
输出：[2,3]


提示：

链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序 排列
 */

#include <stdio.h>
#include <stdlib.h>

#include "../node/listnode.h"
// #include "../hash/hash.h"
/**
*
代码
测试用例
测试用例
测试结果
82. 删除排序链表中的重复元素 II
中等
相关标签
premium lock icon
相关企业
给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表 。



示例 1：


输入：head = [1,2,3,3,4,4,5]
输出：[1,2,5]
示例 2：


输入：head = [1,1,1,2,3]
输出：[2,3]


提示：

链表中节点数目在范围 [0, 300] 内
-100 <= Node.val <= 100
题目数据保证链表已经按升序 排列
 */
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

typedef struct ListNode *ListNode;

struct ListNode *deleteDuplicates(struct ListNode *head) {
    if (head == NULL || head->next == NULL)
        return head;
    hashInit();
    //建立哨兵节点
    ListNode cur = head;
    int arr[301] = {0};
    int i = 0;
    while (cur) {
        int num = cur->val;
        int count = hashGet(num);
        if (count == -1) {
            arr[i++] = num;
            hashPut(num, 0);
        } else
            hashPut(num, count + 1);
        cur = cur->next;
    }
    ListNode sentinel = malloc(sizeof(struct ListNode));
    sentinel->next=NULL;
    ListNode cl = sentinel;
    for (int j = 0; j < i; ++j) {
        int num = arr[j];
        //统计数据为0的值
        if (hashGet(num) == 0) {
            ListNode node = malloc(sizeof(struct ListNode));
            node->val = num;
            node->next = NULL;
            cl->next = node;
            cl = cl->next;
        }
    }
    hashFree();
    head = sentinel->next;
    free(sentinel);
    sentinel = NULL;
    return head;
}

// int main() {
//     // struct ListNode l5 = {5,NULL};
//     // struct ListNode l4 = {4, &l5};
//     // struct ListNode l3 = {2, &l4};
//     struct ListNode l2 = {1, NULL};
//     // struct ListNode l2 = {2, NULL};
//     // struct ListNode l1 = {2, &l2};
//     struct ListNode l1 = {1, &l2};
//     struct ListNode *node = deleteDuplicates(&l1);
//     ListNode lptr = node;
//     while (lptr) {
//         printf("%d ", lptr->val);
//         ListNode tmp = lptr;
//         lptr = lptr->next;
//         free(tmp);
//     }
//     return 0;
// }
