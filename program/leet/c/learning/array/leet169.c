#include <stdio.h>
//
// Created by Administrator on 2026/6/29.
//
/**
* 169. 多数元素
简单
相关标签
premium lock icon
相关企业
给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。



示例 1：

输入：nums = [3,2,3]
输出：3
示例 2：

输入：nums = [2,2,1,1,1,2,2]
输出：2


提示：
n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
输入保证数组中一定有一个多数元素。


进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
 * @return
 */
//最简单也是最能想到的方法就是维护一个哈希表，遍历数组时记录每个值出现的次数
//结束后返回count最大的那个。
//也可以这么想，既然是选出数量占一半以上的那个众数，那就把他们考虑成占领高地的士兵，每个元素代表1个士兵，相同元素代表同一个阵营的
//那在占领高地时如果当前高地上的人与我相同（值相同），那就是同一阵营的士兵，士兵人数count+1，如果不是同一阵营的，就采取同归于尽策略，
//与高地上一个士兵同归于尽，这时count-1.
//当发现高地没有人时，即count=0时，占领高地，并设置上自己的标志。后续出现其他士兵仍然按照以上方式进行count的加减。
//直到最后无论什么顺序遍历，到最后占到高地的总是那个人数过半的士兵
int majorityElement(int *nums, int numsSize) {
    int soldier = 0, count = 0, i = 0;
    for (; i < numsSize; i++) {
        if (!count) {
            count++;
            soldier = nums[i];
        } else if (soldier != nums[i])
            count--;
        else count++;
    }
    return soldier;
}

int main() {
    int arr[] = {2, 2, 1, 1, 1, 2, 2};
    printf("%d\n", majorityElement(arr, sizeof(arr) / sizeof(int)));
    return 0;
}
