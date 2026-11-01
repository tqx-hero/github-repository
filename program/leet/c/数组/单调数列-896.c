/**
896. 单调数列
简单
相关标签
premium lock icon
相关企业
如果数组是单调递增或单调递减的，那么它是 单调 的。

如果对于所有 i <= j，nums[i] <= nums[j]，那么数组 nums 是单调递增的。 如果对于所有 i <= j，nums[i] >= nums[j]，那么数组 nums 是单调递减的。

当给定的数组 nums 是单调数组时返回 true，否则返回 false。

 

示例 1：

输入：nums = [1,2,2,3]
输出：true
示例 2：

输入：nums = [6,5,4,4]
输出：true
示例 3：

输入：nums = [1,3,2]
输出：false
 

提示：

1 <= nums.length <= 105
-105 <= nums[i] <= 105
  */
#include <stdio.h>
 
bool isMonotonic(int* nums, int numsSize) {
	if(numsSize == 1)
		return true;
	int i,order= -1,disorder = -1;
	int sub;
	for(i = 1;i < numsSize;++i){
		sub = nums[i] - nums[i-1];
		if(sub > 0){//如果出现严格单调递增，查看之前是否是递增
			if(order == 0)
				return false;
			disorder = 0; //不允许递减
		}else if (sub < 0 ){//出现严格递减
			if(disorder == 0)
				return false;
			order = 0;
		}
	}
	return true;
}

int main(){
//	int nums[] = {1,2,2,3};
	int nums[] = {1,2,4,3};
	printf("%d\n",isMonotonic(nums,sizeof(nums) / sizeof(int)));
	return 0;
}
