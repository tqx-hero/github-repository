//
// Created by Administrator on 2026/5/24.
//
/**
 *
* @return 643. 子数组最大平均数 I
￼
简单
￼
相关标签
￼
相关企业
￼
给你一个由 n 个元素组成的整数数组 nums 和一个整数 k 。
请你找出平均数最大且 长度为 k 的连续子数组，并输出该最大平均数。
任何误差小于 10-5 的答案都将被视为正确答案。 
示例 1：
输入：
nums = [1,12,-5,-6,50,3], k = 4
输出：
12.75
解释：
最大平均数 (12-5-6+50)/4 = 51/4 = 12.75
示例 2：
输入：
nums = [5], k = 1
输出：
5.00000
  提示：
• n == nums.length
• 1 <= k <= n <= 105
• -104 <= nums[i] <= 104
 */

#include <stdio.h>

double findMaxAverage(int *nums, int numsSize, int k) {
    int cur = 0, max = 0;
    //加载初始值
    for (int i = 0; i < k; ++i)
        cur += nums[i];
    max = cur;
    //移动指针
    for (int left = 1, right = k; right < numsSize; ++right, left++) {
        cur += nums[right] - nums[left - 1];
        max = max > cur ? max : cur;
    }
    return (double) max / k;
}

// int main() {
//     int nums[] = {1, 12, -5, -6, 50, 3};
//     int k = 4;
//     printf("%f\n", findMaxAverage(nums, 6, 4));
//     return 0;
// }
