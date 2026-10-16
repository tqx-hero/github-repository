//
// Created by Administrator on 2026/6/1.
//

#ifndef LEET_CODE_HASH_H
#define LEET_CODE_HASH_H

#endif //LEET_CODE_HASH_H
// 哈希结点
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
static int hashFunc(HASH_MAP_PTR map,int key);

// 初始化哈希表
HASH_MAP_PTR hashInit(int capacity);

// 插入/更新
void hashPut(HASH_MAP_PTR map, int key, int val);

// 查找，不存在返回-1
int hashGet(HASH_MAP_PTR map, int key);

// 删除键
void hashRemove(HASH_MAP_PTR map, int key);

// 释放整张哈希表
void hashFree(HASH_MAP_PTR map);
