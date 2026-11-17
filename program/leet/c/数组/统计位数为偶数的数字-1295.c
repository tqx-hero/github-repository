/**
  1295. 统计位数为偶数的数字
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给你一个整数数组 nums，请你返回其中包含 偶数 个数位的数字的个数。



  示例 1：

  输入：nums = [12,345,2,6,7896]
  输出：2
  解释：
  12 是 2 位数字（位数为偶数） 
  345 是 3 位数字（位数为奇数）  
  2 是 1 位数字（位数为奇数） 
  6 是 1 位数字 位数为奇数） 
  7896 是 4 位数字（位数为偶数）  
  因此只有 12 和 7896 是位数为偶数的数字
  示例 2：

  输入：nums = [555,901,482,1771]
  输出：1 
  解释： 
  只有 1771 是位数为偶数的数字。


  提示：

  1 <= nums.length <= 500
  1 <= nums[i] <= 105
 */
#include <stdio.h>
#include <stdlib.h>

static int total_cnt(int x){
    int num = 0;
    while(x){
        num++;
        x /= 10;
    }
    return num;
}

int findNumbers(int* nums, int numsSize) {
    int ret = 0;
    int cnt,i;
    for(i = 0 ; i < numsSize ; ++i ){
        cnt =  total_cnt(nums[i]);
        if(cnt % 2 == 0)
            ret++;
    }
    return ret;
}

int main(){
    int nums[] = {12,345,2,6,7896};
    fprintf(stdout,"%d\n",findNumbers(nums,sizeof(nums) / sizeof(int)));
    exit(0);
}
