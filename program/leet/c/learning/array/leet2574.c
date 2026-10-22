//
// Created by Administrator on 2026/6/23.
//
/**
* 2574. 左右元素和的差值
简单
相关标签
premium lock icon
相关企业
提示
给你一个下标从 0 开始的长度为 n 的整数数组 nums。

定义两个数组 leftSum 和 rightSum，其中：

leftSum[i] 是数组 nums 中下标 i 左侧元素之和。如果不存在对应的元素，leftSum[i] = 0 。
rightSum[i] 是数组 nums 中下标 i 右侧元素之和。如果不存在对应的元素，rightSum[i] = 0 。
返回长度为 n 数组 answer，其中 answer[i] = |leftSum[i] - rightSum[i]|。



示例 1：

输入：nums = [10,4,8,3]
输出：[15,1,11,22]
解释：数组 leftSum 为 [0,10,14,22] 且数组 rightSum 为 [15,11,3,0] 。
数组 answer 为 [|0 - 15|,|10 - 11|,|14 - 3|,|22 - 0|] = [15,1,11,22] 。
示例 2：

输入：nums = [1]
输出：[0]
解释：数组 leftSum 为 [0] 且数组 rightSum 为 [0] 。
数组 answer 为 [|0 - 0|] = [0] 。


提示：

1 <= nums.length <= 1000
1 <= nums[i] <= 105
 * @return
 */

#include <stdio.h>
#include <stdlib.h>

int *leftRightDifference(int *nums, int numsSize, int *returnSize) {
    *returnSize = numsSize;
    int *ret = calloc(numsSize, sizeof(int));
    if (numsSize == 1)
        return ret;
    int i = 0, right = 0, left = 0;
    for (; i < numsSize; i++)
        right += nums[i];
    //第二次遍历直接计算左右之差,在取绝对值
    for (i = 0; i < numsSize; i++) {
        int num = nums[i];
        ret[i] = abs(right - left - num);
        right -= num;
        left += num;
    }
    return ret;
}

int main() {
    int arr[] = {10, 4, 8, 3}, size;
    int *ans = leftRightDifference(arr, sizeof(arr) / sizeof(int), &size);
    for (int i = 0; i < size; ++i)
        printf("%d ", ans[i]);
    free(ans);
    return 0;
}
