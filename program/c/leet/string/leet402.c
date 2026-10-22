#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//
// Created by Administrator on 2026/6/9.
//
/**
*
代码
测试用例
测试用例
测试结果
402. 移掉 K 位数字
中等
相关标签
premium lock icon
相关企业
给你一个以字符串表示的非负整数 num 和一个整数 k ，移除这个数中的 k 位数字，使得剩下的数字最小。请你以字符串形式返回这个最小的数字。


示例 1 ：

输入：num = "1432219", k = 3
输出："1219"
解释：移除掉三个数字 4, 3, 和 2 形成一个新的最小的数字 1219 。
示例 2 ：

输入：num = "10200", k = 1
输出："200"
解释：移掉首位的 1 剩下的数字为 200. 注意输出不能有任何前导零。
示例 3 ：

输入：num = "10", k = 2
输出："0"
解释：从原数字移除所有的数字，剩余为空就是 0 。


提示：

1 <= k <= num.length <= 105
num 仅由若干位数字（0 - 9）组成
除了 0 本身之外，num 不含任何前导零
 * @return
 */
//先看第一个[0,k-1]区间,即下标为k的值是否是0，如果是0，去掉第一个区间相当于把后面的0也去掉，能多去几位，所以直接遍历后面即可
//如果第k个值不是0，那就需要记录每个k区间的第一个值，遍历到字符串最后，找出最大值的下标截取即可
//TODO 这个算法是适用于连续移除k个元素的场景
#define HASH_SIZE 10   // 质数，减少冲突
#define HASHNODE Node *
// 哈希结点


typedef struct Node {
    int index;
    struct Node *next;
} Node;


// 初始化哈希表
void hashInit(HASHNODE buckets[]) {
    for (int i = 0; i < HASH_SIZE; ++i) {
        buckets[i] = NULL;
    }
}

void add(HASHNODE buckets[], int index, int begin) {
    HASHNODE node = buckets[index];
    HASHNODE n = malloc(sizeof(Node));
    n->index = begin;
    n->next = NULL;
    if (node)
        n->next = node;
    buckets[index] = n;
}

//基数排序查找最大数
int getMaxIndex(int is[], int iCount, char *num, int k) {
    if (iCount == 1)
        return is[0];
    //统计is数组中的下标个数，大于1时需要再次判断k区间内字符串的大小
    //需要对每个字符串的[begin+1,begin+k-1]这k-1个字符进行基数排序，找出最大值来
    //需要k-1到1倒着排，为什么没比0号位置，因为0号位置已经全部相同了，没必要在比较
    Node *bucket[HASH_SIZE];
    hashInit(bucket);
    int i = 0, j = k - 1;
    for (; j >= 1; --j) {
        for (i = 0; i < iCount; ++i) {
            //起始下标index
            int begin = is[i];
            //当前要入桶的下标
            int curIndx = begin + j;
            //当前要比较的字符
            char c = num[curIndx];
            add(bucket, c - '0', begin);
        }
        //收集一波以后需要倒桶，从前往后收集
        int count = 0;
        for (int m = 0; m < HASH_SIZE; ++m) {
            HASHNODE node = bucket[m];
            //node存在，拿出来往数组中装入
            while (node) {
                is[count++] = node->index;
                HASHNODE tmp = node;
                node = node->next;
                free(tmp);
                tmp = NULL;
            }
        }
        hashInit(bucket);
    }
    //排序完成后找到数组is最后一个即为最大值的下标
    int maxIndex = is[iCount - 1];
    //free
    for (i = 0; i < HASH_SIZE; ++i) {
        HASHNODE node = bucket[i];
        while (node) {
            HASHNODE tmp = node;
            node = node->next;
            free(tmp);
            tmp = NULL;
        }
    }
    return maxIndex;
}

char *removeKdigits(char *num, int k) {
    int size = (int) strlen(num);
    char *ret = (char *) malloc(size + 1);
    if (k == size) {
        *ret = '0';
        *(ret + 1) = '\0';
        return ret;
    }
    int i = 0, count = 0;
    //判断第k个元素是否为0，如果是，直接截取
    if (*(num + k) == '0') {
        //省略掉前导0
        for (i = k; i < size && *(num + i) == '0'; ++i);
        for (; i < size; ++i, count++)
            *(ret + count) = *(num + i);
        if (!count)
            *(ret + count++) = '0';
        *(ret + count) = '\0';
        return ret;
    }
    //如果不满足以上条件，开始找最大值开始的下标
    char max = 0;
    int iSize = ceil((double)size / k);
    int end = size - k,
            //is数组存放出现相同第一个值时的原数组起始下标
            is[iSize], iCount = 0;
    for (i = 0; i <= end; ++i) {
        char c = *(num + i);
        //大于时，替换max,同时更新is数组
        if (c > max) {
            max = c;
            *is = i;
            iCount = 1;
        }
        //等于时，添加到is数组
        else if (c == max)
            *(is + iCount++) = i;
    }
    int cur = getMaxIndex(is, iCount, num, k);
    //读取cur下标前面的数据拷贝到新字符数组
    count = 0;
    for (i = 0; i < cur; ++i, count++)
        *(ret + count) = *(num + i);

    for (i = cur + k; i < size; ++i, count++)
        *(ret + count) = *(num + i);
    *(ret + count) = '\0';
    return ret;
}

int main() {
    // char *nums = "1432219";
    // char *nums = "10200";
    // char *nums = "144456";
    char *nums = "33526221184202197273";
    // char *nums = "10";
    char *ret = removeKdigits(nums, 19);
    printf("%s\n", ret);
    free(ret);
    return 0;
}
