//
// Created by Administrator on 2026/6/21.
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
Q3. 最大连续 1 的个数
￼
简单
￼
相关标签
￼
相关企业
￼
提示
￼
给定一个二进制数组 nums ， 计算其中最大连续 1 的个数。 
示例 1：
输入：
nums = [1,1,0,1,1,1]
输出：
3
解释：
开头的两位和最后的三位都是连续 1 ，所以最大连续 1 的个数是 3.
示例 2:
输入：
nums = [1,0,1,1,0,1]
输出：
2
  提示：
• 1 <= nums.length <= 105
• nums[i] 不是 0 就是 1.
 * @return
 */

#include <stdio.h>

int findMaxConsecutiveOnes(int *nums, int numsSize) {
    int ans = 0, i = 0, cur = 0;
    for (; i < numsSize; i++) {
        if (!nums[i]) {
            //判断已经数了几个1，超过ans的就替换，不超过就直接置0
            if (cur && cur > ans)
                ans = cur;
            cur = 0;
        } else
            cur++;
    }
    return ans >= cur ? ans : cur;
}

int main() {
    int arr[] = {1, 1, 0, 1, 1, 1};
    printf("%d\n", findMaxConsecutiveOnes(arr, sizeof(arr) / sizeof(int)));
    return 0;
}
