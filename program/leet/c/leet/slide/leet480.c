//
// Created by Administrator on 2026/6/14.
//
/**
*
代码
测试用例
测试用例
测试结果
480. 滑动窗口中位数
困难
相关标签
premium lock icon
相关企业
提示
中位数是有序序列最中间的那个数。如果序列的长度是偶数，则没有最中间的数；此时中位数是最中间的两个数的平均数。

例如：

[2,3,4]，中位数是 3
[2,3]，中位数是 (2 + 3) / 2 = 2.5
给你一个数组 nums，有一个长度为 k 的窗口从最左端滑动到最右端。窗口中有 k 个数，每次窗口向右移动 1 位。你的任务是找出每次窗口移动后得到的新窗口中元素的中位数，并输出由它们组成的数组。



示例：

给出 nums = [1,3,-1,-3,5,3,6,7]，以及 k = 3。

窗口位置                      中位数
---------------               -----
[1  3  -1] -3  5  3  6  7       1
 1 [3  -1  -3] 5  3  6  7      -1
 1  3 [-1  -3  5] 3  6  7      -1
 1  3  -1 [-3  5  3] 6  7       3
 1  3  -1  -3 [5  3  6] 7       5
 1  3  -1  -3  5 [3  6  7]      6
 因此，返回该滑动窗口的中位数数组 [1,-1,-1,3,5,6]。



提示：

你可以假设 k 始终有效，即：k 始终小于等于输入的非空数组的元素个数。
与真实值误差在 10 ^ -5 以内的答案将被视作正确答案。
 * @return
 */

#define HASH_SIZE 1009   // 质数，减少冲突
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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

//由于需要对k个值排序，首先需要有一个k大小的数组 ak[k],用来存放每个k区间内的数值所在原数组的下标
//这k个值不是一成不变的，随着窗口的滑动每次变化一位，所以需要用一个哈希表存储原数组下标i与当前数组ak的下标关系
//这样在减去左指针、增加右指针时可以立即找到数据项所在ak数组的位置。
//1、刚开始的前k项直接排序，所以可以使用函数库里面的快排qsort，保证时间复杂度O(nlogn)
//排完后就直接找中间的数值计算即可，k为奇数就找中间位置的值，转换成a[i]；k为偶数就找到a[(k-1)>>1]与a[1+((k-1)>>1)]相加除以2
//同时还需更新哈希表对应关系
//2、之后每次在ak[]基础上进行-left，+right操作，由于ak是有序数组，增减一项只需要排列这一个增加后的数据项即可，
//所以使用插入排序。
//1/通过哈希表找到left指针所在的ak下标m并记录，删除哈希表这一项。
//2/比较a[right]与a[left]的大小，如果大于left，则需要排列的是ak数组[m,k-1]区间的值，直接插入排序即可。排序的同时可以维护哈希表
//3/小于left值，排列的那就是[0,m]区间，同样按照上述步骤执行
//每次排列后取中间值计算中位数

static const int *g_arr;
static const int *ak_arr;
bool even = true;
int k_size;

static int compare(const void *a, const void *b) {
    long long rea=(long long)g_arr[*(int *) a];
    long long reb=(long long)g_arr[*(int *) b];
    if (rea>reb)
        return 1;
    if (rea ==reb)
        return 0;
    return -1;
}

//计算数组的中位数
double sumMiddle() {
    int mid = (k_size - 1) >> 1;
    if (even)
        return  (double)(((double)g_arr[ak_arr[mid]]/10 + (double)g_arr[ak_arr[mid + 1]]/10) / 2.0)*10;
    return (double) g_arr[ak_arr[mid]];
}

//直接插入排序[begin,end]区间内的数值，结束后返回target插入的所在数组的下标
//target为nums数组下标
//order为按什么顺序插入：0：从后往前逆序，1：从前往后顺序
int insertSort(int *ak, int begin, int end, int target, int order) {
    if (begin == end) {
        ak[begin] = target;
        return begin;
    }
    int targetNum = g_arr[target];
    int i;
    if (order) {
        i = begin + 1;
        //从前往后查找，begin位是空位
        for (; i <= end; ++i) {
            int idx = ak[i];
            //如果i+1 < i,前移
            if (g_arr[idx] < targetNum) {
                ak[i - 1] = idx;
                continue;
            }
            break;
        }
        //大于等于时就不需要再排序了，将target放入i-1即可
        ak[i - 1] = target;
        return i - 1;
    }
    //逆序排列，从后往前找位置
    i = end - 1;
    for (; i >= begin; i--) {
        int idx = ak[i];
        //如果i-1 >目标值
        if (g_arr[idx] > targetNum) {
            ak[i + 1] = idx;
            continue;
        }
        break;
    }
    //小于等于时，停止排序
    ak[i + 1] = target;
    return i + 1;
}

void updateHash(int *ak, int begin, int end) {
    for (int i = begin; i <= end; ++i)
        hashPut(ak[i], i);
}

double *medianSlidingWindow(int *nums, int numsSize, int k, int *returnSize) {
    g_arr = NULL;
    ak_arr = NULL;
    even = true;
    k_size = 0;
    *returnSize = numsSize - k + 1;
    double *ret = (double *) calloc(*returnSize, sizeof(double));
    hashInit();
    //赋值全局指针，用于快排
    int ak[k], aki = 0, i = 0;
    k_size = k;
    ak_arr = ak;
    g_arr = nums;
    //判断是否偶数
    if (k & 0x1)
        even = false;
    //初始化数组ak
    for (; i < k; ++i)
        ak[i] = i;
    //对前k个值进行快排
    qsort((void *) ak, k, sizeof(int), compare);
    //更新哈希表
    for (i = 0; i < k; ++i) {
        hashPut(ak[i], i);
    }
    //找到第一个中位数，放入结果集ret
    ret[aki++] = sumMiddle();
    int left = 1, right = k, curIdx, index = 0, prev;
    for (; right < numsSize; left++, right++, aki++) {
        prev = left - 1;
        //获取删除的left下标所在ak数组的下标
        index = hashGet(prev);
        hashRemove(prev);
        //如果删除的数据项与添加的数据项相同
        //不需要再查找，直接复制前一个中位数即可
        //同时更新这个索引位的下标
        if (nums[prev] == nums[right]) {
            ret[aki] = ret[aki - 1];
            //更新索引
            hashPut(right, index);
            ak[index] = right;
        } else {
            if (nums[prev] > nums[right]) {
                //原nums[left]>nums[right],直接排序比较前[0,index]个数据，同时添加right
                curIdx = insertSort(ak, 0, index, right, 0);
                //更新[curIdx,index]内的哈希值
                updateHash(ak, curIdx, index);
            } else {
                curIdx = insertSort(ak, index, k - 1, right, 1);
                //更新哈希值区间变为了[index,curIdx]
                updateHash(ak, index, curIdx);
            }
            //计算中位数
            ret[aki] = sumMiddle();
        }
    }
    hashFree();
    return ret;
}
//思路是对的，就是在leetcode超时，这个算法的时间复杂度是O(n*k),具体要用两个堆的方式，时间复杂度到O(nlogn)，实现方式已用java实现
int main() {
    // int nums[]={1,3,-1,-3,5,3,6,7};
    // int nums[]={1,4,2,3};
    // int nums[]={2147483647,2147483647};
    // int nums[]={-2147483648,-2147483648,2147483647,-2147483648,-2147483648,-2147483648,2147483647,2147483647,2147483647,2147483647,-2147483648,2147483647,-2147483648};
    int nums[]={-2147483648,-2147483648,2147483647,-2147483648,1,3,-2147483648,-100,8,17,22,-2147483648,-2147483648,2147483647,2147483647,2147483647,2147483647,-2147483648,2147483647,-2147483648};
    int k=6,size;
    double *ret= medianSlidingWindow(nums,sizeof(nums)/sizeof(int),k,&size);
    for (int i = 0; i < size; ++i) {
        printf("%f ",ret[i]);
    }
    free(ret);
    return 0;
}
