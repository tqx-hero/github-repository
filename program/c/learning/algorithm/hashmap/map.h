#ifndef __HASH_MAP_
#define __HASH_MAP_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 哈希表桶大小，质数减少冲突
#define HASH_TABLE_SIZE 101

// 哈希节点
typedef struct HashNode {
    int key;
    void* value;
    struct HashNode* next;
} HashNode;

// 哈希表结构体
typedef struct HashTable {
    HashNode** buckets;
    int bucket_size;
} HashTable;

typedef void (*HashVisitCb)(int key, void* value);


unsigned int hash_func(int key);
HashTable* hash_table_create(void);
int hash_table_put(HashTable* ht, int key, void* value);
void* hash_table_get(HashTable* ht, int key);
int hash_table_remove(HashTable* ht, int key);
void hash_table_foreach(HashTable* ht, HashVisitCb cb);
void hash_table_destroy(HashTable* ht);
#endif