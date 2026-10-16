//
// Created by Administrator on 2026/6/24.
//
/**
*
代码
测试用例
测试用例
测试结果
706. 设计哈希映射
简单
相关标签
premium lock icon
相关企业
不使用任何内建的哈希表库设计一个哈希映射（HashMap）。

实现 MyHashMap 类：

MyHashMap() 用空映射初始化对象
void put(int key, int value) 向 HashMap 插入一个键值对 (key, value) 。如果 key 已经存在于映射中，则更新其对应的值 value 。
int get(int key) 返回特定的 key 所映射的 value ；如果映射中不包含 key 的映射，返回 -1 。
void remove(key) 如果映射中存在 key 的映射，则移除 key 和它所对应的 value 。


示例：

输入：
["MyHashMap", "put", "put", "get", "get", "put", "get", "remove", "get"]
[[], [1, 1], [2, 2], [1], [3], [2, 1], [2], [2], [2]]
输出：
[null, null, null, 1, -1, null, 1, null, -1]

解释：
MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // myHashMap 现在为 [[1,1]]
myHashMap.put(2, 2); // myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(1);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(3);    // 返回 -1（未找到），myHashMap 现在为 [[1,1], [2,2]]
myHashMap.put(2, 1); // myHashMap 现在为 [[1,1], [2,1]]（更新已有的值）
myHashMap.get(2);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,1]]
myHashMap.remove(2); // 删除键为 2 的数据，myHashMap 现在为 [[1,1]]
myHashMap.get(2);    // 返回 -1（未找到），myHashMap 现在为 [[1,1]]


提示：

0 <= key, value <= 106
最多调用 104 次 put、get 和 remove 方法
 * @return
 */
#define HASH_SET_MAX_SIZE 5023
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HashEntry {
    int key;
    int value;
    struct HashEntry *next;
} HashEntry;

typedef struct {
    HashEntry *buckets[HASH_SET_MAX_SIZE];
} MyHashMap;

int getIndex(int key) {
    return key % HASH_SET_MAX_SIZE;
}

MyHashMap *myHashMapCreate() {
    MyHashMap *map = calloc(HASH_SET_MAX_SIZE, sizeof(HashEntry *));
    if (!map) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    return map;
}

void myHashMapPut(MyHashMap *obj, int key, int value) {
    int index = getIndex(key);
    HashEntry *entry_ptr = obj->buckets[index];
    HashEntry *cur = entry_ptr;
    //存在则更新
    while (cur) {
        if (cur->key == key) {
            cur->value = value;
            return;
        }
        cur = cur->next;
    }
    //不存在则添加
    HashEntry *newEntry = malloc(sizeof(HashEntry));
    if (!newEntry) {
        printf("%s\n", strerror(errno));
        return;
    }
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = entry_ptr;
    obj->buckets[index] = newEntry;
}

int myHashMapGet(MyHashMap *obj, int key) {
    HashEntry *entry_ptr = obj->buckets[getIndex(key)];
    HashEntry *cur = entry_ptr;
    while (cur) {
        if (cur->key == key)
            return cur->value;
        cur = cur->next;
    }
    return -1;
}

void myHashMapRemove(MyHashMap *obj, int key) {
    int index = getIndex(key);
    HashEntry *entry = obj->buckets[index];
    HashEntry *prev = entry;
    //第一个元素即为要删除的元素时
    if (!prev)
        return;
    if (prev->key == key) {
        obj->buckets[index] = prev->next;
        prev->next = NULL;
        free(prev);
        prev = NULL;
    } else {
        HashEntry *cur = prev->next;
        while (cur) {
            if (cur->key == key) {
                //删除这个节点
                prev->next = cur->next;
                cur->next = NULL;
                free(cur);
                cur = NULL;
                return;
            }
            cur = cur->next;
            prev = prev->next;
        }
    }
}

void myHashMapFree(MyHashMap *obj) {
    for (int i = 0; i < HASH_SET_MAX_SIZE; ++i) {
        HashEntry *entry = obj->buckets[i];
        while (entry) {
            HashEntry *next = entry->next;
            entry->next = NULL;
            free(entry);
            entry = next;
        }
        obj->buckets[i] = NULL;
    }
    free(obj);
    obj = NULL;
}

int main() {
    /*MyHashMap myHashMap = new MyHashMap();
myHashMap.put(1, 1); // myHashMap 现在为 [[1,1]]
myHashMap.put(2, 2); // myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(1);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,2]]
myHashMap.get(3);    // 返回 -1（未找到），myHashMap 现在为 [[1,1], [2,2]]
myHashMap.put(2, 1); // myHashMap 现在为 [[1,1], [2,1]]（更新已有的值）
myHashMap.get(2);    // 返回 1 ，myHashMap 现在为 [[1,1], [2,1]]
myHashMap.remove(2); // 删除键为 2 的数据，myHashMap 现在为 [[1,1]]
myHashMap.get(2);    // 返回 -1（未找到），myHashMap 现在为 [[1,1]]*/
    MyHashMap *map = myHashMapCreate();
    myHashMapPut(map, 1, 1);
    myHashMapPut(map, 2, 2);
    printf("%d\n", myHashMapGet(map, 1));
    printf("%d\n", myHashMapGet(map, 3));
    myHashMapPut(map, 2, 1);
    printf("%d\n", myHashMapGet(map, 2));
    myHashMapRemove(map, 2);
    printf("%d\n", myHashMapGet(map, 2));
    myHashMapFree(map);
    return 0;
}
