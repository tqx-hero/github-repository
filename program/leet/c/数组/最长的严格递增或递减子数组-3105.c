#include <stdio.h>
#include <stdlib.h>
/**
  3105. 最长的严格递增或递减子数组
  简单
  相关标签
  premium lock icon
  相关企业
  给你一个整数数组 nums 。

  返回数组 nums 中 严格递增 或 严格递减 的最长非空子数组的长度。



  示例 1：

  输入：nums = [1,4,3,3,2]

  输出：2

  解释：

  nums 中严格递增的子数组有[1]、[2]、[3]、[3]、[4] 以及 [1,4] 。

  nums 中严格递减的子数组有[1]、[2]、[3]、[3]、[4]、[3,2] 以及 [4,3] 。

  因此，返回 2 。

  示例 2：

  输入：nums = [3,3,3,3]

  输出：1

  解释：

  nums 中严格递增的子数组有 [3]、[3]、[3] 以及 [3] 。

  nums 中严格递减的子数组有 [3]、[3]、[3] 以及 [3] 。

  因此，返回 1 。

  示例 3：

  输入：nums = [3,2,1]

  输出：3

  解释：

  nums 中严格递增的子数组有 [3]、[2] 以及 [1] 。

  nums 中严格递减的子数组有 [3]、[2]、[1]、[3,2]、[2,1] 以及 [3,2,1] 。

  因此，返回 3 。



  提示：

  1 <= nums.length <= 50
  1 <= nums[i] <= 50
 */

int longestMonotonicSubarray(int* nums, int numsSize) {
    if(numsSize == 1)
        return 1;
    int cur_len = 1,i,subval,ret = 0;
    int ordered = 0;
    for(i = 1;i < numsSize;++i){
        subval = nums[i] - nums[i - 1];
        if(subval > 0 && ordered >= 0){
            cur_len++;
            ordered = 1;
        }
        else if(subval < 0 && ordered <= 0){
            cur_len++;
            ordered = -1;
        }
        else{
            ordered = subval;
            ret = ret >= cur_len ? ret : cur_len;
            cur_len = subval ? 2 : 1;
        }
    }
    return cur_len >= ret ? cur_len : ret;
}

int main(){
    //    int nums[] = {3,3,3,3};
    int nums[] = {1,5,2,7};
    fprintf(stdout,"%d\n",longestMonotonicSubarray(nums,sizeof(nums) / sizeof(int)));
    exit(0);
}
