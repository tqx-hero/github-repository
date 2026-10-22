//
// Created by Administrator on 2026/6/20.
//
/**
*
代码
测试用例
测试用例
测试结果
1840. 最高建筑高度
困难
相关标签
premium lock icon
相关企业
提示
在一座城市里，你需要建 n 栋新的建筑。这些新的建筑会从 1 到 n 编号排成一列。

这座城市对这些新建筑有一些规定：

每栋建筑的高度必须是一个非负整数。
第一栋建筑的高度 必须 是 0 。
任意两栋相邻建筑的高度差 不能超过  1 。
除此以外，某些建筑还有额外的最高高度限制。这些限制会以二维整数数组 restrictions 的形式给出，其中 restrictions[i] = [idi, maxHeighti] ，表示建筑 idi 的高度 不能超过 maxHeighti 。

题目保证每栋建筑在 restrictions 中 至多出现一次 ，同时建筑 1 不会 出现在 restrictions 中。

请你返回 最高 建筑能达到的 最高高度 。



示例 1：


输入：n = 5, restrictions = [[2,1],[4,1]]
输出：2
解释：上图中的绿色区域为每栋建筑被允许的最高高度。
我们可以使建筑高度分别为 [0,1,2,1,2] ，最高建筑的高度为 2 。
示例 2：


输入：n = 6, restrictions = []
输出：5
解释：上图中的绿色区域为每栋建筑被允许的最高高度。
我们可以使建筑高度分别为 [0,1,2,3,4,5] ，最高建筑的高度为 5 。
示例 3：


输入：n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
输出：5
解释：上图中的绿色区域为每栋建筑被允许的最高高度。
我们可以使建筑高度分别为 [0,1,2,3,3,4,4,5,4,3] ，最高建筑的高度为 5 。


提示：

2 <= n <= 109
0 <= restrictions.length <= min(n - 1, 105)
2 <= idi <= n
idi 是 唯一的 。
0 <= maxHeighti <= 109
 * @return
 */

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000009   // 质数，减少冲突
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

static int compare(const void *a, const void *b) {
    return *((int *) b) - *((int *) a);
}

static inline int max(int x, int y) {
    return x >= y ? x : y;
}

void adjustHeight(int begin, int end, int *maxHeights, int order) {
    int curHeight, i, j;
    //order =1,顺序；0，逆序
    if (order) {
        curHeight = maxHeights[begin] + 1;
        i = begin + 1;
        j = end;
        for (; i <= j; i++) {
            if (maxHeights[i] <= curHeight)
                break;
            maxHeights[i] = curHeight++;
        }
    } else {
        curHeight = maxHeights[end] + 1;
        i = end - 1;
        j = begin;
        for (; i >= j; i--) {
            if (maxHeights[i] <= curHeight)
                break;
            maxHeights[i] = curHeight++;
        }
    }
}

//[[8,5],[9,0],[6,2],[4,0],[3,2],[10,0],[5,3],[7,3],[2,4]]
int maxBuilding(int n, int **restrictions, int restrictionsSize, int *restrictionsColSize) {
    if (restrictionsSize == 0)
        return n - 1;
    int maxHeights[n + 1], i = 1;
    for (; i <= n; i++) {
        maxHeights[i] = i - 1;
    }
    //按照楼层号降序排列
   // qsort(restrictions, restrictionsSize, sizeof(int *), compare);
    for (i = 0; i < restrictionsSize; ++i) {
        //获取当前的[id,maxHeight]
        int *restriction = restrictions[i];
        int id = restriction[0];
        int curHeight = restriction[1];
        //更新当前楼层的高度
        //如果当前楼层高度小于已经设定的高度，则需要以这个楼层为基准，上下去更新楼层最大高度
        if (restriction[1] >= maxHeights[id])
            continue;
        //小于当前楼层高度，则需要左右调整
        maxHeights[id] = curHeight;
        //更新相邻楼层的最大高度
        //更新取当前楼层最大值与计算的楼层高度最小值
        adjustHeight(id, n, maxHeights, 1);
        adjustHeight(0, id, maxHeights, 0);
    }
    int maxCurHeight = 0;
    for (i = n; i > 0; i--)
        maxCurHeight = max(maxCurHeight, maxHeights[i]);
    return maxCurHeight;
}

int main() {
    //n = 10, restrictions = [[5,3],[2,5],[7,4],[10,3]]
    // int arr1[] = {5, 3};
    // int arr2[] = {7, 4};
    // int arr3[] = {10, 3};
    // int n = 10, *restrictions[] = {arr1, arr2, arr3}, num = 2;

    //n=10, [[8,5],[9,0],[6,2],[4,0],[3,2],[10,0],[5,3],[7,3],[2,4]]
    int arr1[] = {8, 5};
    int arr2[] = {9, 0};
    int arr3[] = {6, 2};
    int arr4[] = {4, 0};
    int arr5[] = {3, 2};
    int arr6[] = {10, 0};
    int arr7[] = {5, 3};
    int arr8[] = {7, 3};
    int arr9[] = {2, 4};
    int n = 10, *restrictions[] = {arr1, arr2, arr3, arr4, arr5, arr6, arr7, arr8, arr9}, num = 2;
    // int arr1[] = {2, 1};
    // int arr2[] = {4, 1};
    // int n = 5, *restrictions[] = {arr1, arr2}, num = 2;
    printf("%d\n", maxBuilding(n, restrictions, sizeof(restrictions) / sizeof(int *), &num));
    return 0;
}
