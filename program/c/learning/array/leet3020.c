//
// Created by Administrator on 2026/6/27.
//
/**
* 3020. 子集中元素的最大数量
中等
相关标签
premium lock icon
相关企业
提示
给你一个 正整数 数组 nums 。

你需要从数组中选出一个满足下述条件的子集：

你可以将选中的元素放置在一个下标从 0 开始的数组中，并使其遵循以下模式：[x, x2, x4, ..., xk/2, xk, xk/2, ..., x4, x2, x]（注意，k 可以是任何 非负 的 2 的幂）。例如，[2, 4, 16, 4, 2] 和 [3, 9, 3] 都符合这一模式，而 [2, 4, 8, 4, 2] 则不符合。
返回满足这些条件的子集中，元素数量的 最大值 。



示例 1：

输入：nums = [5,4,1,2,2]
输出：3
解释：选择子集 {4,2,2} ，将其放在数组 [2,4,2] 中，它遵循该模式，且 22 == 4 。因此答案是 3 。
示例 2：

输入：nums = [1,3,2,4]
输出：1
解释：选择子集 {1}，将其放在数组 [1] 中，它遵循该模式。因此答案是 1 。注意我们也可以选择子集 {2} 、{4} 或 {3} ，可能存在多个子集都能得到相同的答案。


提示：

2 <= nums.length <= 105
1 <= nums[i] <= 109
 * @return
 */


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_MAP_PTR HashMap*

typedef struct HashNode {
    unsigned int key;
    int val;
    struct HashNode *next;
} HashNode;

typedef struct HashMap {
    unsigned int size, count;
    HashNode *buckets[];
} HashMap;

// 哈希映射函数
static unsigned int hashFunc(HASH_MAP_PTR map, unsigned int key) {
    return key % map->size;
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
void hashPut(HASH_MAP_PTR map, unsigned int key, int val) {
    unsigned int idx = hashFunc(map, key);
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
int hashGet(HASH_MAP_PTR map, unsigned int key) {
    unsigned int idx = hashFunc(map, key);
    HashNode *cur = map->buckets[idx];
    while (cur) {
        if (cur->key == key)
            return cur->val;
        cur = cur->next;
    }
    return -1;
}

// 删除键
void hashRemove(HASH_MAP_PTR map, unsigned int key) {
    unsigned int idx = hashFunc(map, key);
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

//直接运用哈希表存储数据，键值对key:value为：nums[i] : count,count为该值出现的次数
//再次遍历数组，查找每个元素在哈希表内出现的次数，如果count=1，记录该数据满足的子集数量为1，i++
//如果count>=2，就需要依次查看哈希表内nums[i]^2,nums[i]^4...出现的次数，每出现1次，count+=2,直到出现的次数=1或者值>65535为止
//因为整型最大值2^31-1开平方后最大值不超过2^16-1,即65535，大于这个数的值平方必定会超过整型最大范围
int maximumLength(int *nums, int numsSize) {
    //设定数据最大值65535，超过该值的数据不需要统计它的平方值
    unsigned int max_int = (1 << 16) - 1;
    HASH_MAP_PTR map = hashInit(numsSize);
    int i = 0;
    //将所有数据放入哈希表，同时以出现的次数作为value
    for (; i < numsSize; i++) {
        int num = nums[i], count;
        //哈希表中不存在添加
        if ((count = hashGet(map, num)) == -1)
            count = 0;
        hashPut(map, num, count + 1);
    }
    int max_len = 0;
    for (i = 0; i < numsSize; i++) {
        unsigned int num = nums[i];
        int count = 1;
        //如果数据为1
        if (num == 1) {
            count = hashGet(map, num);
            count = count & 1 ? count : count - 1;
        } else {
            //如果只出现一次，那以此为一次方的数据的数组子集只能是一个
            //再有一种就是它的值超过65535
            //如果出现2次以上，那么需要考虑它的平方是否出现过的可能
            unsigned int square = 0;
            int s_count = 0;
            //该数据*2
            while (num <= max_int && hashGet(map, num) >= 2 && (s_count = hashGet(map, square = (int) pow(num, 2))) >
                   0) {
                count += 2;
                if (s_count == 1)
                    break;
                num = square;
            }
        }
        max_len = max(count, max_len);
    }
    hashFree(map);
    return max_len;
}

int main() {
    int nums[] = {15, 15, 225, 225, 50625, 50625};
    // int nums[] = {1, 1};
    // int nums[] = {5,4,1,2,2};
    // int nums[] = {1, 3, 2, 4};
    printf("%d\n", maximumLength(nums, sizeof(nums) / sizeof(int)));
    return 0;
}
