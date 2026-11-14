/**
  3364. 最小正和子数组
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给你一个整数数组 nums 和 两个 整数 l 和 r。你的任务是找到一个长度在 l 和 r 之间（包含）且和大于 0 的 子数组 的 最小 和。

  返回满足条件的子数组的 最小 和。如果不存在这样的子数组，则返回 -1。

  子数组 是数组中的一个连续 非空 元素序列。



  示例 1：

  输入： nums = [3, -2, 1, 4], l = 2, r = 3

  输出： 1

  解释：

  长度在 l = 2 和 r = 3 之间且和大于 0 的子数组有：

  [3, -2] 和为 1
  [1, 4] 和为 5
  [3, -2, 1] 和为 2
  [-2, 1, 4] 和为 3
  其中，子数组 [3, -2] 的和为 1，是所有正和中最小的。因此，答案为 1。

  示例 2：

  输入： nums = [-2, 2, -3, 1], l = 2, r = 3

  输出： -1

  解释：

  不存在长度在 l 和 r 之间且和大于 0 的子数组。因此，答案为 -1。

  示例 3：

  输入： nums = [1, 2, 3, 4], l = 2, r = 4

  输出： 3

  解释：

  子数组 [1, 2] 的长度为 2，和为 3，是所有正和中最小的。因此，答案为 3。



  提示：

  1 <= nums.length <= 100
  1 <= l <= r <= nums.length
  -1000 <= nums[i] <= 1000
 */
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int min(const int x,const int y){
    return x <= y ? x : y;
}

int minimumSumSubarray(int* nums, int numsSize, int l, int r) {
    int ret,i,j,temp;
    int *prefix;
    if((prefix = malloc(sizeof(int) *(numsSize + 1))) == NULL){
        perror("malloc()");
        exit(1);
    }
    prefix[0] = 0;
    for(i = 0;i < numsSize;++i)
        prefix[i + 1] = prefix[i] + nums[i];
    ret = INT_MAX;
    for(i = 0;i < numsSize;++i){
        for(j = l;j <= r && i+j <= numsSize;++j){
            temp = prefix[i + j] - prefix[i];
            if(temp > 0)
                ret = min(temp,ret);
        }
    }
    free(prefix);
    return ret == INT_MAX ? -1 : ret;  
}

int main(){
    int nums[] = {3, -2, 1, 4};
    int l = 2,r = 3;
    fprintf(stdout,"%d\n",minimumSumSubarray(nums,sizeof(nums) / sizeof(int),l,r)); 
    exit(0);
}
