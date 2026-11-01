#include <stdio.h>
//
// Created by Administrator on 2026/6/19.
//
/**
*
代码
测试用例
测试用例
测试结果
413. 等差数列划分
中等
相关标签
premium lock icon
相关企业
如果一个数列 至少有三个元素 ，并且任意两个相邻元素之差相同，则称该数列为等差数列。

例如，[1,3,5,7,9]、[7,7,7,7] 和 [3,-1,-5,-9] 都是等差数列。
给你一个整数数组 nums ，返回数组 nums 中所有为等差数组的 子数组 个数。

子数组 是数组中的一个连续序列。



示例 1：

输入：nums = [1,2,3,4]
输出：3
解释：nums 中有三个子等差数组：[1, 2, 3]、[2, 3, 4] 和 [1,2,3,4] 自身。
示例 2：

输入：nums = [1]
输出：0


提示：

1 <= nums.length <= 5000
-1000 <= nums[i] <= 1000
 * @return
 */
//从i=1开始，计算int sub = a[i]-a[i-1];同时设置初始count=2（初始只有2个数）
//指针往后移动i++，继续计算a[i]-a[i-1],查看结果是否与sub相同，相同则count++，指针继续后移
//当结果不同时，统计count，如果大于等于3，则计算等差数列个数为num = (count-1)(count-2)/2,结果并入ret
//如果count不大于3，重新设置sub为新的a[i]-a[i-1],count = 2,这样遍历到数组结束，返回结果
int numberOfArithmeticSlices(int *nums, int numsSize) {
    if (numsSize < 3)
        return 0;
    int num = 0, count = 2, sub = nums[1] - nums[0], i = 2;
    for (; i < numsSize; i++) {
        int curSub = nums[i] - nums[i - 1];
        if (curSub == sub)
            count++;
        else {
            if (count >= 3)
                num += (count - 1) * (count - 2) / 2;
            count = 2;
            sub = curSub;
        }
    }
    if (count >= 3)
        num += (count - 1) * (count - 2) / 2;
    return num;
}

int main() {
    int arr[] = {1, 2, 3, 4};
    printf("%d\n", numberOfArithmeticSlices(arr, sizeof(arr) / sizeof(int)));
    return 0;
}
