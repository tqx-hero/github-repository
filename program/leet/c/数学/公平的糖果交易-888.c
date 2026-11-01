/**
888. 公平的糖果交换
简单
相关标签
premium lock icon
相关企业
爱丽丝和鲍勃拥有不同总数量的糖果。给你两个数组 aliceSizes 和 bobSizes ，aliceSizes[i] 是爱丽丝拥有的第 i 盒糖果中的糖果数量，bobSizes[j] 是鲍勃拥有的第 j 盒糖果中的糖果数量。

两人想要互相交换一盒糖果，这样在交换之后，他们就可以拥有相同总数量的糖果。一个人拥有的糖果总数量是他们每盒糖果数量的总和。

返回一个整数数组 answer，其中 answer[0] 是爱丽丝必须交换的糖果盒中的糖果的数目，answer[1] 是鲍勃必须交换的糖果盒中的糖果的数目。如果存在多个答案，你可以返回其中 任何一个 。题目测试用例保证存在与输入对应的答案。

 

示例 1：

输入：aliceSizes = [1,1], bobSizes = [2,2]
输出：[1,2]
示例 2：

输入：aliceSizes = [1,2], bobSizes = [2,3]
输出：[1,2]
示例 3：

输入：aliceSizes = [2], bobSizes = [1,3]
输出：[2,3]
示例 4：

输入：aliceSizes = [1,2,5], bobSizes = [2,4]
输出：[5,4]
 

提示：

1 <= aliceSizes.length, bobSizes.length <= 104
1 <= aliceSizes[i], bobSizes[j] <= 105
爱丽丝和鲍勃的糖果总数量不同。
题目数据保证对于给定的输入至少存在一个有效答案。
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
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

int add_nums(int *arr,int size){
	int i,ret = 0;
	for(i = 0;i < size;++i)
		ret += arr[i];
	return ret;
}

int* fairCandySwap(int* aliceSizes, int aliceSizesSize, int* bobSizes, int bobSizesSize, int* returnSize) {
	int * ret;
	int alice_num,bob_num,idx,sub,add;
	HASH_MAP_PTR hash_map;
	ret = malloc(sizeof(int) * 2);
	if(!ret){
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	*returnSize = 2;
	alice_num = add_nums(aliceSizes,aliceSizesSize);
	bob_num = add_nums(bobSizes,bobSizesSize);
	//使用哈希表缓存alice的每个值
	hash_map = hashInit(aliceSizesSize);
	for(idx = 0;idx < aliceSizesSize;++idx)
		hashPut(hash_map,aliceSizes[idx],0);
	sub = abs(alice_num - bob_num) >> 1;
	if(alice_num > bob_num){
		//alice比bob多，那就遍历bob查找map中比当前元素大sub的值
		for(idx = 0;idx < bobSizesSize;++idx)
			if(hashGet(hash_map,(add = sub + bobSizes[idx])) != -1)
				break;
	}else{
		//alice比bob少，那就查找map中比当前元素小sub的值
		for(idx = 0;idx < bobSizesSize;++idx)
			if(hashGet(hash_map,(add = bobSizes[idx] - sub)) != -1)
				break;
	}
	ret[0] = add;
	ret[1] = bobSizes[idx];
	hashFree(hash_map);
	return ret;
}

int main(){
	int aliceSizes[] = {1,1}, bobSizes[] = {2,2};
	int *ret,returnSize;
	ret = fairCandySwap(aliceSizes,sizeof(aliceSizes) / sizeof(int),bobSizes,sizeof(bobSizes) / sizeof(int),&returnSize);
	printf("%d %d \n" ,ret[0],ret[1]);
	free(ret);
	return 0;
}
