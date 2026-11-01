/**
453. 最小操作次数使数组元素相等
中等
相关标签
premium lock icon
相关企业
给你一个长度为 n 的整数数组，每次操作将会使 n - 1 个元素增加 1 。返回让数组所有元素相等的最小操作次数。

 

示例 1：

输入：nums = [1,2,3]
输出：3
解释：
只需要3次操作（注意每次操作会增加两个元素的值）：
[1,2,3]  =>  [2,3,3]  =>  [3,4,3]  =>  [4,4,4]
示例 2：

输入：nums = [1,1,1]
输出：0
 

提示：

n == nums.length
1 <= nums.length <= 105
-109 <= nums[i] <= 109
答案保证符合 32-bit 整数
  */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
//找到最小值，统计每个元素与最小值的差，相加就是结果
int minMoves(int* nums, int numsSize) {
	int min,sum = 0;
	int i;
	min = INT_MAX;
	for(i = 0;i < numsSize; ++i) //统计最小值
		min = min <= nums[i] ? min : nums[i];
	for(i = 0;i < numsSize;++i)
		sum += nums[i] - min;
	return sum;
}

int main(){
	int nums[] = {1,2,3};
	printf("%d \n", minMoves(nums,sizeof(nums) / sizeof(int)));
	return 0;
}
