//
// Created by Administrator on 2026/6/28.
//
/**
* 1171. 从链表中删去总和值为零的连续节点
中等
相关标签
premium lock icon
相关企业
提示
给你一个链表的头节点 head，请你编写代码，反复删去链表中由 总和 值为 0 的连续节点组成的序列，直到不存在这样的序列为止。

删除完毕后，请你返回最终结果链表的头节点。



你可以返回任何满足题目要求的答案。

（注意，下面示例中的所有序列，都是对 ListNode 对象序列化的表示。）

示例 1：

输入：head = [1,2,-3,3,1]
输出：[3,1]
提示：答案 [1,2,1] 也是正确的。
示例 2：

输入：head = [1,2,3,-3,4]
输出：[1,2,4]
示例 3：

输入：head = [1,2,3,-3,-2]
输出：[1]


提示：

给你的链表中可能有 1 到 1000 个节点。
对于链表中的每个节点，节点的值：-1000 <= node.val <= 1000.
 * @return
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../node/listnode.h"

#define HASH_MAP_PTR HashMap*

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
    int size = max(capacity, 11);
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


struct ListNode *removeZeroSumSublists(struct ListNode *head) {
    //一个元素的情况直接返回
    if (!head->next) {
        if (head->val == 0)
            return NULL;
        return head;
    }
    //多个节点时，需要创建数组来处理
    struct ListNode *node_arr[1001];
    int ans_arr[1001];
    int count = 0;
    struct ListNode *cur = head;
    while (cur) {
        node_arr[count++] = cur;
        cur = cur->next;
    }
    //添加哨兵节点
    node_arr[count++] = NULL;
    //创建前缀和数组
    int prefix_sums[1001] = {0}, i = 1;
    for (; i < count; i++)
        prefix_sums[i] = node_arr[i - 1]->val + prefix_sums[i - 1];
    HashMap *map = hashInit(1001);
    //放入哈希表，比较值，更新ans数组
    int ans_count = 0;
    for (i = 0; i < count; i++) {
        //如果之前没有缓存过该前缀和，那就把下标放入ans数组
        int beforeIndex;
        if ((beforeIndex = hashGet(map, prefix_sums[i])) != -1) {
            //如果之前出现过该前缀和，表明从那个index到这个index之间的数值之和为0，弹栈直到弹出那个index为止
            int j = ans_count - 1,tmp;
            for (; j >= 0 && (tmp=ans_arr[j]) != beforeIndex; j--)
                hashRemove(map, prefix_sums[tmp]);
            //替换该位置的下标为当前下标i
            ans_count = j >= 0 ? j : 0;
        }
        ans_arr[ans_count++] = i;
        hashPut(map, prefix_sums[i], i);
    }
    //统计结束后把ans数组内的各节点连接起来即可
    struct ListNode sentinel = {-1,NULL};
    cur = &sentinel;
    for (i = 0; i < ans_count - 1; i++) {
        cur->next = node_arr[ans_arr[i]];
        cur = cur->next;
    }
    cur->next = node_arr[ans_arr[i]];
    hashFree(map);
    return sentinel.next;
}

int main() {
    struct ListNode node5 = {1,NULL};
    struct ListNode node4 = {3, &node5};
    struct ListNode node3 = {-3, &node4};
    struct ListNode node2 = {2, &node3};
    struct ListNode node1 = {1, &node2};
    struct ListNode *list_node = removeZeroSumSublists(&node1);
    while (list_node) {
        printf("%d\n", list_node->val);
        list_node = list_node->next;
    }
    return 0;
}
