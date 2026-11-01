//
// Created by Administrator on 2026/6/1.
//
#include <stdlib.h>

#include "hash.h"

#include <stdio.h>
#include <string.h>

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
