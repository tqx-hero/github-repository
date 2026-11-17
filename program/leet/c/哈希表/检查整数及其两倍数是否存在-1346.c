/**
1346. 检查整数及其两倍数是否存在
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 arr，请你检查是否存在两个整数 N 和 M，满足 N 是 M 的两倍（即，N = 2 * M）。

更正式地，检查是否存在两个下标 i 和 j 满足：

i != j
0 <= i, j < arr.length
arr[i] == 2 * arr[j]
 

示例 1：

输入：arr = [10,2,5,3]
输出：true
解释：N = 10 是 M = 5 的两倍，即 10 = 2 * 5 。
示例 2：

输入：arr = [7,1,14,11]
输出：true
解释：N = 14 是 M = 7 的两倍，即 14 = 2 * 7 。
示例 3：

输入：arr = [3,1,7,11]
输出：false
解释：在该情况下不存在 N 和 M 满足 N = 2 * M 。
 

提示：

2 <= arr.length <= 500
-10^3 <= arr[i] <= 10^3
  */
#include "../hash/hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

HASH_MAP_PTR hash_map;

static void uninstall(void)
{
    hashFree(hash_map);    
}

bool checkIfExist(int* arr, int arrSize) {
    int i,zero = 0;
    hash_map = hashInit(arrSize);
    atexit(uninstall);
    for(i = 0;i < arrSize;++i)
    {
        if(arr[i] == 0)
            zero++;
        else
            hashPut(hash_map,arr[i],i);
    }
    if(zero > 1)
        return true;
    for( i = 0;i < arrSize && hashGet(hash_map,arr[i] * 2) == -1;++i);
    return i != arrSize;
}

int main(){
    int arr[] = {-16,-13,8};
    int arrSize = 3;
    fprintf(stdout,"%d\n",checkIfExist(arr,arrSize));
    exit(0);
}
