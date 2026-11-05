/**
 * 
 * 977. 有序数组的平方
简单
相关标签
premium lock icon
相关企业
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

 

示例 1：

输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
示例 2：

输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
 

提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 已按 非递减顺序 排序
 

进阶：

请你设计时间复杂度为 O(n) 的算法解决本问题
 */
#include <stdio.h>
#include <stdlib.h>

int* sortedSquares(int* nums, int numsSize, int* returnSize) {
    int *ret,left,right,i;
    if((ret = malloc(numsSize * sizeof(int))) == NULL){
        perror("malloc() error");
        exit(1);
    }
    for(i = 0;i < numsSize;++i)
        nums[i] *= nums[i];
    *returnSize = numsSize;
    //双指针，分别从左右两边往中间靠拢
    for(i = numsSize -1, left = 0,right = numsSize - 1;i >= 0;--i){
        if(nums[left] >= nums[right])
            ret[i] = nums[left++];
        else
            ret[i] = nums[right--];
    }
    return ret;
}
int main(){
    int nums[] = {-4,-1,0,3,10},retrunSize;
    int *ret = sortedSquares(nums,sizeof(nums) / sizeof(int),&retrunSize);
    for(int i = 0;i < retrunSize;++i)
        fprintf(stdout,"%d ",ret[i]);
    fprintf(stdout,"\n");
    free(ret);
    return 0;
}
