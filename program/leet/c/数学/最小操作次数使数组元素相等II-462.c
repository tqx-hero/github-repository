/**
462. 最小操作次数使数组元素相等 II
中等
相关标签
premium lock icon
相关企业
给你一个长度为 n 的整数数组 nums ，返回使所有数组元素相等需要的最小操作数。

在一次操作中，你可以使数组中的一个元素加 1 或者减 1 。

测试用例经过设计以使答案在 32 位 整数范围内。

 

示例 1：

输入：nums = [1,2,3]
输出：2
解释：
只需要两次操作（每次操作指南使一个元素加 1 或减 1）：
[1,2,3]  =>  [2,2,3]  =>  [2,2,2]
示例 2：

输入：nums = [1,10,2,9]
输出：16
 

提示：

n == nums.length
1 <= nums.length <= 105
-109 <= nums[i] <= 109
  */
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int minMoves2(int* nums, int numsSize) {
    //先计算和，求平均值，
    long long sum =0;
    double age;
    int i,floor_int,ceil_int,cnt,ceil_cnt;
    for(i = 0;i < numsSize;++i)
	sum += nums[i];

    age = sum * 1.0 / numsSize;
    cnt = 0;
    floor_int = floor(age);
    for(i = 0;i < numsSize;++i)
	cnt += abs(nums[i] - floor_int);
    if(floor_int == age)
	return cnt;
    ceil_int = ceil(age);
    ceil_cnt = 0;
    for(i = 0;i < numsSize;++i)
	ceil_cnt += abs(nums[i] - ceil_cnt);
    return cnt <= ceil_cnt ? cnt : ceil_cnt;
}

int main(){
    int nums[] = {1,2,3};
    printf("%d \n",minMoves2(nums,sizeof(nums) / sizeof(int)));
	return 0;
}
