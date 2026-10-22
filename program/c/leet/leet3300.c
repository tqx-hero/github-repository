//
// Created by Administrator on 2026/6/1.
//
/**
*
￼
代码
￼
测试用例
测试用例
￼
测试结果
3300. 替换为数位和以后的最小元素
￼
简单
￼
相关标签
￼
相关企业
￼
提示
￼
给你一个整数数组 nums 。
请你将 nums 中每一个元素都替换为它的各个数位之 和 。
请你返回替换所有元素以后 nums 中的 最小 元素。 
示例 1：
输入：nums = [10,12,13,14]
输出：1
解释：
nums 替换后变为 [1, 3, 4, 5] ，最小元素为 1 。
示例 2：
输入：nums = [1,2,3,4]
输出：1
解释：
nums 替换后变为 [1, 2, 3, 4] ，最小元素为 1 。
示例 3：
输入：nums = [999,19,199]
输出：10
解释：
nums 替换后变为 [27, 10, 19] ，最小元素为 10 。 
提示：
• 1 <= nums.length <= 100
• 1 <= nums[i] <= 104
 */

#include <stdio.h>

int minElement(int *nums, int numsSize) {
    int resNum = __INT_MAX__;
    for (int i = 0; i < numsSize; ++i) {
        int minNum = 0;
        int num = *(nums + i);
        while (num) {
            minNum += num % 10;
            num /= 10;
        }
        if (minNum == 1)
            return 1;
        resNum = resNum > minNum ? minNum : resNum;
    }
    return resNum;
}

// int main() {
//     int arr []  ={999,19,199};
//     int m = minElement(arr,3);
//     printf("%d\n",m);
//     return 0;
// }
