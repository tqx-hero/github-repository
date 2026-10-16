//
// Created by Administrator on 2026/6/11.
//

#include <stdio.h>
/**
* 209. 长度最小的子数组
中等
相关标签
premium lock icon
相关企业
给定一个含有 n 个正整数的数组和一个正整数 target 。

找出该数组中满足其总和大于等于 target 的长度最小的 子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。



示例 1：

输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
示例 2：

输入：target = 4, nums = [1,4,4]
输出：1
示例 3：

输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0


提示：

1 <= target <= 109
1 <= nums.length <= 105
1 <= nums[i] <= 104


进阶：

如果你已经实现 O(n) 时间复杂度的解法, 请尝试设计一个 O(n log(n)) 时间复杂度的解法。
 * @return
 */
//双指针，left、right，当res<target时，res+=a[++right]
//res>target 有两种情况：
//1、left=right：res=a[++left];right++;
//2、left<right: res-=a[left++];
//当res=target时，计算len= right-left+1，更新minLen
int minSubArrayLen(int target, int *nums, int numsSize) {
    //先取首元素放入
    int res = *nums, left = 0, right = 1, minLen = numsSize + 1;
    if (res >= target)
        return 1;
    if (numsSize == 1)
        return 0;
    res += *(nums + right);
    for (; right < numsSize;) {
        if (res < target) {
            if (right + 1 < numsSize)
                res += *(nums + ++right);
            else
                break;
        } else {
            int len = right - left + 1;
            minLen = len < minLen ? len : minLen;
            //判断left=right?
            if (left == right) {
                if (right + 1 < numsSize) {
                    res = *(nums + ++left);
                    right++;
                    continue;
                }
                break;
            }
            res -= *(nums + left++);
        }
    }
    return minLen == numsSize + 1 ? 0 : minLen;
}

int main() {
    int a[] = {1, 2, 3, 4, 5};
    // int a[] = {1, 1, 1, 1, 1, 1, 1, 1};
    // int a[] = {1,4,4};
    // int a[] = {2, 3, 1, 2, 4, 3};
    printf("%d\n", minSubArrayLen(11, a, 5));
    return 0;
}
