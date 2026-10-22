//
// Created by Administrator on 2026/6/8.
//

/**
*
代码
测试用例
测试用例
测试结果
2161. 根据给定数字划分数组
中等
相关标签
premium lock icon
相关企业
提示
给你一个下标从 0 开始的整数数组 nums 和一个整数 pivot 。请你将 nums 重新排列，使得以下条件均成立：

所有小于 pivot 的元素都出现在所有大于 pivot 的元素 之前 。
所有等于 pivot 的元素都出现在小于和大于 pivot 的元素 中间 。
小于 pivot 的元素之间和大于 pivot 的元素之间的 相对顺序 不发生改变。
更正式的，考虑每一对 pi，pj ，pi 是初始时位置 i 元素的新位置，pj 是初始时位置 j 元素的新位置。如果 i < j 且两个元素 都 小于（或大于）pivot，那么 pi < pj 。
请你返回重新排列 nums 数组后的结果数组。



示例 1：

输入：nums = [9,12,5,10,14,3,10], pivot = 10
输出：[9,5,3,10,10,12,14]
解释：
元素 9 ，5 和 3 小于 pivot ，所以它们在数组的最左边。
元素 12 和 14 大于 pivot ，所以它们在数组的最右边。
小于 pivot 的元素的相对位置和大于 pivot 的元素的相对位置分别为 [9, 5, 3] 和 [12, 14] ，它们在结果数组中的相对顺序需要保留。
示例 2：

输入：nums = [-3,4,3,2], pivot = 2
输出：[-3,2,4,3]
解释：
元素 -3 小于 pivot ，所以在数组的最左边。
元素 4 和 3 大于 pivot ，所以它们在数组的最右边。
小于 pivot 的元素的相对位置和大于 pivot 的元素的相对位置分别为 [-3] 和 [4, 3] ，它们在结果数组中的相对顺序需要保留。


提示：

1 <= nums.length <= 105
-106 <= nums[i] <= 106
pivot 等于 nums 中的一个元素。
 * @return
 */

#include <stdio.h>
#include <stdlib.h>

int *pivotArray(int *nums, int numsSize, int pivot, int *returnSize) {
    if (numsSize == 1) {
        *returnSize = 1;
        return nums;
    }
    int count = 0;
    int lower[numsSize], greater[numsSize];
    int i = 0, lj = 0, gj = 0;
    for (; i < numsSize; ++i) {
        int cur = *(nums + i);
        if (cur == pivot)
            count++;
        else if (cur < pivot)
            *(lower + lj++) = cur;
        else
            *(greater + gj++) = cur;
    }
    //拼装新数组即可
    *returnSize = count + lj + gj;
    int *ret = malloc((*returnSize) * sizeof(int));
    int j = 0;
    for (i = 0; i < lj; ++i)
        *(ret + j++) = *(lower + i);
    //拼装pivot
    for (i = 0; i < count; ++i)
        *(ret + j++) = pivot;

    for (i = 0; i < gj; ++i)
        *(ret + j++) = *(greater + i);
    return ret;
}

int main() {
    int arr[] = {9, 12, 5, 10, 14, 3, 10};
    int size;
    int *ret = pivotArray(arr, 7, 10, &size);
    for (int i = 0; i < size; ++i) {
        printf("%d ", ret[i]);
    }
    free(ret);
    return 0;
}
