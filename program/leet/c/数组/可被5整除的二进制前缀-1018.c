/**
1018. 可被 5 整除的二进制前缀
简单
相关标签
premium lock icon
相关企业
提示
给定一个二进制数组 nums ( 索引从0开始 )。

我们将xi 定义为其二进制表示形式为子数组 nums[0..i] (从最高有效位到最低有效位)。

例如，如果 nums =[1,0,1] ，那么 x0 = 1, x1 = 2, 和 x2 = 5。
返回布尔值列表 answer，只有当 xi 可以被 5 整除时，答案 answer[i] 为 true，否则为 false。

 

示例 1：

输入：nums = [0,1,1]
输出：[true,false,false]
解释：
输入数字为 0, 01, 011；也就是十进制中的 0, 1, 3 。只有第一个数可以被 5 整除，因此 answer[0] 为 true 。
示例 2：

输入：nums = [1,1,1]
输出：[false,false,false]
 

提示：

1 <= nums.length <= 105 
nums[i] 仅为 0 或 1
  */
#include <stdio.h>
#include <stdlib.h>
//TODO 需要考虑更多情况： 5-0101. 10-1010. 15-1111. 20-10100
#if 0
void* Malloc(size_t sz){
	void * ret;
	if(!(ret = malloc(sz))){
		perror("malloc() error");
		exit(1);
	}
	return ret;
}

bool is_div_by5(int *nums,int left,int right){
	if(left < 0)
		left = 0;
	int num = 0;
	for(;left <= right;++left)
		num = num * 2 + nums[left];
	return num % 5 == 0;
}

bool* prefixesDivBy5(int* nums, int numsSize, int* returnSize) {
	bool* ret = Malloc(sizeof(bool) * numsSize);
	*returnSize = numsSize;
	bool config = (nums[0] == 0);
	for(int i = 0;i < numsSize;++i){
		if(nums[i] == 0){
			if(config)
				ret[i] = true;
			else
				ret[i] = false;
		}else{
			//等于1时，更新最右边的1下标为i，再判断
			config = is_div_by5(nums,i - 3,i); 
			ret[i] = config;
		}
	}
	return ret;
}

int main(){
	int nums[] = {0,1,1};
	int returnSize;
	bool *ret = prefixesDivBy5(nums,sizeof(nums) / sizeof(int) , &returnSize);
	for(int i =0;i < returnSize;++i)
		fprintf(stdout,"%d ",ret[i]);
	fprintf(stdout,"\n");
	free(ret);
	return 0;
}
#endif
