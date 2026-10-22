//
// Created by Administrator on 2026/6/25.
//
/**
* 817. 链表组件
中等
相关标签
premium lock icon
相关企业
给定链表头结点 head，该链表上的每个结点都有一个 唯一的整型值 。同时给定列表 nums，该列表是上述链表中整型值的一个子集。

返回列表 nums 中组件的个数，这里对组件的定义为：链表中一段最长连续结点的值（该值必须在列表 nums 中）构成的集合。



示例 1：



输入: head = [0,1,2,3], nums = [0,1,3]
输出: 2
解释: 链表中,0 和 1 是相连接的，且 nums 中不包含 2，所以 [0, 1] 是 nums 的一个组件，同理 [3] 也是一个组件，故返回 2。
示例 2：



输入: head = [0,1,2,3,4], nums = [0,3,1,4]
输出: 2
解释: 链表中，0 和 1 是相连接的，3 和 4 是相连接的，所以 [0, 1] 和 [3, 4] 是两个组件，故返回 2。


提示：

链表中节点数为n
1 <= n <= 104
0 <= Node.val < n
Node.val 中所有值 不同
1 <= nums.length <= n
0 <= nums[i] < n
nums 中所有值 不同
 * @return
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../node/listnode.h"

#define HASH_MAP_PTR HashMap*
typedef struct ListNode *list_ptr;

// 哈希结点
typedef struct HashNode {
    int key;
    int val;
    struct HashNode *next;
} HashNode;

typedef struct HashMap {
    int size, count;
    HashNode *buckets[];
} HashMap;

// 哈希映射函数
static int hashFunc(HASH_MAP_PTR map, int key) {
    return abs(key) % map->size;
}

static inline int max(int x, int y) {
    return x >= y ? x : y;
}

// 初始化哈希表
HASH_MAP_PTR hashInit(int capacity) {
    int size = max((capacity >> 1) + 1, 11);
    HASH_MAP_PTR map = malloc(sizeof(HashMap) + size * sizeof(HashNode *));
    if (!map) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    map->size = size;
    map->count = 0;
    for (int i = 0; i < size; i++)
        map->buckets[i] = NULL;
    return map;
}

// 插入/更新
void hashPut(HASH_MAP_PTR map, int key, int val) {
    int idx = hashFunc(map, key);
    HashNode *cur = map->buckets[idx];
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
    newNode->next = map->buckets[idx];
    map->buckets[idx] = newNode;
    map->count++;
}

// 查找，不存在返回-1
int hashGet(HASH_MAP_PTR map, int key) {
    int idx = hashFunc(map, key);
    HashNode *cur = map->buckets[idx];
    while (cur) {
        if (cur->key == key)
            return cur->val;
        cur = cur->next;
    }
    return -1;
}

// 删除键
void hashRemove(HASH_MAP_PTR map, int key) {
    int idx = hashFunc(map, key);
    HashNode **p = &map->buckets[idx];
    while (*p) {
        if ((*p)->key == key) {
            HashNode *del = *p;
            *p = (*p)->next;
            free(del);
            return;
        }
        p = &(*p)->next;
    }
    map->count--;
}

// 释放整张哈希表
void hashFree(HASH_MAP_PTR map) {
    for (int i = 0; i < map->size; i++) {
        HashNode *cur = map->buckets[i];
        while (cur) {
            HashNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
        map->buckets[i] = NULL;
    }
    free(map);
}

int numComponents(struct ListNode *head, int *nums, int numsSize) {
    HASH_MAP_PTR map = hashInit(numsSize);
    if (!map)
        return -1;
    int i = 0;
    for (; i < numsSize; i++)
        hashPut(map, nums[i], 0);
    list_ptr cur = head;
    int ret = 0, count = 0;
    while (cur) {
        if (!hashGet(map, cur->val))
            count++;
            //如果不存在，判断count是否大于0，大于0则将ret++，count=0
        else if (count) {
            ret++;
            count = 0;
        }
        cur = cur->next;
    }
    hashFree(map);
    return count ? ret + 1 : ret;
}

int main() {
    int nums[] = {0, 1, 3};
    struct ListNode node4 = {3,NULL};
    struct ListNode node3 = {2, &node4};
    struct ListNode node2 = {1, &node3};
    struct ListNode node1 = {0, &node2};
    int ret = numComponents(&node1, nums, sizeof(nums) / sizeof(int));
    printf("%d\n", ret);
    return 0;
}
