#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
// Created by Administrator on 2026/6/10.
//
/**
 *
 * @return
 */
//

#define HASH_SIZE 100001   // 质数，减少冲突

// 哈希结点
typedef struct HashNode {
    int key;
    int val;
    struct HashNode *next;
} HashNode;

HashNode *hashTable[HASH_SIZE];

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

char *removeKdigits(char *num, int k) {
    int size = (int) strlen(num);
    int sz = size - k >= 2 ? size - k + 1 : 2;
    char *ret = (char *) malloc(sz);
    if (k == size) {
        *ret = '0';
        *(ret + 1) = '\0';
        return ret;
    }
    int zeroIndex[size], counts[10] = {0};
    int i = 0, count = 0;
    for (; i < size; ++i) {
        int n = num[i] - '0';
        //记录0的下标以及所有数值的数量
        if (!n)
            zeroIndex[counts[0]] = i;
        counts[n]++;
    }
    //查看首个k字符区间内有无0
    int zNum = 0, idx;
    i = 0;
    while (1) {
        //大于k，则即使删除0~k-1项也不会出现前导0，这时候需要挑最大值进行删除
        if (counts[0] == 0 || (idx = zeroIndex[zNum]) - i > k) {
            //统计从最大值开始需要删除哪几个
            hashInit();
            //将他们入哈希表
            for (int j = 9, ct = 0; j >= 0 && ct < k; --j) {
                while (counts[j] > 0 && ct < k) {
                    int get = hashGet(j);
                    if (get <= 0)
                        hashPut(j, 1);
                    else
                        hashPut(j, get + 1);
                    ct++;
                    counts[j]--;
                }
            }
            for (; i < size; ++i) {
                int get = hashGet(num[i] - '0');
                //如果哈希表中不存在，则添加到结果集中
                if (get <= 0) {
                    ret[count++] = num[i];
                } else {
                    //如果存在哈希表，说明需要删除，
                    hashPut(num[i] - '0', get - 1);
                }
            }
            ret[count] = '\0';
            return ret;
        }
        //如果有idx<=k时，说明这k项有前导0，需要先删除idx之前的所有数据
        for (; i < idx; ++i) {
            counts[num[i] - '0']--;
            k--;
        }
        i++;
        zNum++;
        counts[0]--;
    }
}

int main() {
    char a[] = "1432219";
    // char a[] = "10200";
    char *p;
    printf("%s\n", p = removeKdigits(a, 3));
    free(p);
    return 0;
}
