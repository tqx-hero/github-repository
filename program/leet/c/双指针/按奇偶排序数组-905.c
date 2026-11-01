/**
905. 按奇偶排序数组
简单
相关标签
premium lock icon
相关企业
给你一个整数数组 nums，将 nums 中的的所有偶数元素移动到数组的前面，后跟所有奇数元素。

返回满足此条件的 任一数组 作为答案。

 

示例 1：

输入：nums = [3,1,2,4]
输出：[2,4,3,1]
解释：[4,2,3,1]、[2,4,1,3] 和 [4,2,1,3] 也会被视作正确答案。
示例 2：

输入：nums = [0]
输出：[0]
 

提示：

1 <= nums.length <= 5000
0 <= nums[i] <= 5000
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int* sortArrayByParity(int* nums, int numsSize, int* returnSize) {
	int *ret;
	int left,right;
	ret = malloc(sizeof(int) * numsSize);
	if(!ret){
		perror("malloc error ");
		exit(EXIT_FAILURE);
	}
	*returnSize = numsSize;
	memcpy(ret,nums,sizeof(int) * numsSize);
	for(left = -1,right = 0;right < numsSize;++right){
		if(ret[right] % 2){ //如果是奇数，left为-1，就设置left
			if(left == -1)
				left = right;
		}else{//如果是偶数，且left不等于-1，开始调换
			if(left != -1){
				int temp = ret[left];
				ret[left] = ret[right];
				ret[right] = temp;
				left++;
			}
		}
	}
	return ret;
}

int main(){
	int arr[] = {3,1,2,4},returnSize;
	int *ret = sortArrayByParity(arr,sizeof(arr) / sizeof(int),&returnSize);
	for(int i = 0;i < returnSize;++i)
		printf("%d ",ret[i]);
	printf("\n");
	free(ret);
	return 0;
}
