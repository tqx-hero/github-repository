//
// Created by Administrator on 2026/6/24.
//
/**
* 705. 设计哈希集合
简单
相关标签
premium lock icon
相关企业
不使用任何内建的哈希表库设计一个哈希集合（HashSet）。

实现 MyHashSet 类：

void add(key) 向哈希集合中插入值 key 。
bool contains(key) 返回哈希集合中是否存在这个值 key 。
void remove(key) 将给定值 key 从哈希集合中删除。如果哈希集合中没有这个值，什么也不做。

示例：

输入：
["MyHashSet", "add", "add", "contains", "contains", "add", "contains", "remove", "contains"]
[[], [1], [2], [1], [3], [2], [2], [2], [2]]
输出：
[null, null, null, true, false, null, true, null, false]

解释：
MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // 返回 True
myHashSet.contains(3); // 返回 False ，（未找到）
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // 返回 True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // 返回 False ，（已移除）


提示：

0 <= key <= 106
最多调用 104 次 add、remove 和 contains
 * @return
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_SET_MAX_SIZE 5023

typedef struct HashEntry {
    int key;
    struct HashEntry *next;
} HashEntry;

typedef struct {
    HashEntry *buckets[HASH_SET_MAX_SIZE];
} MyHashSet;


MyHashSet *myHashSetCreate() {
    MyHashSet *set = calloc(HASH_SET_MAX_SIZE, sizeof(HashEntry *));
    if (!set) {
        printf("%s\n", strerror(errno));
        return NULL;
    }
    return set;
}

int getIndex(int key) {
    return key % HASH_SET_MAX_SIZE;
}

bool myHashSetContains(MyHashSet *obj, int key) {
    HashEntry *entry_ptr = obj->buckets[getIndex(key)];
    HashEntry *cur = entry_ptr;
    while (cur) {
        if (cur->key == key)
            return true;
        cur = cur->next;
    }
    return false;
}

void myHashSetAdd(MyHashSet *obj, int key) {
    if (myHashSetContains(obj, key))
        return;
    HashEntry *newEntry = malloc(sizeof(HashEntry));
    if (!newEntry) {
        printf("%s\n", strerror(errno));
        return;
    }
    int index = getIndex(key);
    HashEntry *entry = obj->buckets[index];
    newEntry->key = key;
    newEntry->next = entry;
    obj->buckets[index] = newEntry;
}

void myHashSetRemove(MyHashSet *obj, int key) {
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


void myHashSetFree(MyHashSet *obj) {
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
    /*MyHashSet myHashSet = new MyHashSet();
myHashSet.add(1);      // set = [1]
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(1); // 返回 True
myHashSet.contains(3); // 返回 False ，（未找到）
myHashSet.add(2);      // set = [1, 2]
myHashSet.contains(2); // 返回 True
myHashSet.remove(2);   // set = [1]
myHashSet.contains(2); // 返回 False ，（已移除）*/
    MyHashSet * set = myHashSetCreate();
    myHashSetAdd(set, 1);
    myHashSetAdd(set, 2);
    printf("%d\n",myHashSetContains(set, 1));
    printf("%d\n",myHashSetContains(set, 3));
    myHashSetAdd(set, 2);
    printf("%d\n",myHashSetContains(set, 2));
    myHashSetRemove(set, 2);
    printf("%d\n",myHashSetContains(set, 2));
    myHashSetFree(set);
    return 0;
}
