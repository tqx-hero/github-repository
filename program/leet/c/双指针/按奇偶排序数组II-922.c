/**
922. 按奇偶排序数组 II
简单
相关标签
premium lock icon
相关企业
给定一个非负整数数组 nums，  nums 中一半整数是 奇数 ，一半整数是 偶数 。

对数组进行排序，以便当 nums[i] 为奇数时，i 也是 奇数 ；当 nums[i] 为偶数时， i 也是 偶数 。

你可以返回 任何满足上述条件的数组作为答案 。

 

示例 1：

输入：nums = [4,2,5,7]
输出：[4,5,2,7]
解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。
示例 2：

输入：nums = [2,3]
输出：[2,3]
 

提示：

2 <= nums.length <= 2 * 104
nums.length 是偶数
nums 中一半是偶数
0 <= nums[i] <= 1000
 

进阶：可以不使用额外空间解决问题吗？
  */
#include <stdlib.h>
#include <stdio.h>

int* sortArrayByParityII(int* nums, int numsSize, int* returnSize) {
	int *ret,oddp,evenp;
	if((ret = malloc(sizeof(int) * numsSize)) == NULL){
		perror("malloc error");
		exit(EXIT_FAILURE);
	}
	*returnSize = numsSize;
	for(oddp = 1,evenp = 0;oddp < numsSize || evenp < numsSize;oddp += 2,evenp += 2){
		//双指针移动，偶数指针找到值为奇数，奇数指针找到值等于偶数的
		for(;evenp < numsSize;evenp += 2){
			if(nums[evenp] % 2 == 0) //如果是偶数，直接放入
				ret[evenp] = nums[evenp];
			//如果是奇数，跳出循环，移动奇数指针
			else 
				break;
		}
		for(;oddp < numsSize ;oddp += 2){
			if(nums[oddp] % 2) //如果是奇数，填入相关位置
				ret[oddp] = nums[oddp];
			else 
				break;
		}
		if(oddp < numsSize && evenp < numsSize){
			ret[oddp] = nums[evenp];
			ret[evenp] = nums[oddp];
		}
	}
	return ret;
}

int main(){
	int nums[] = {4,2,5,7},*ret,returnSize;
	ret = sortArrayByParityII(nums,sizeof(nums) / sizeof(int) , &returnSize);
	for(int i = 0;i < returnSize;++i)
		printf("%d ",ret[i]);
	printf("\n");
	free(ret);
	return 0;
}
