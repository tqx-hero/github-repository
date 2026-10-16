//
// Created by Administrator on 2026/6/21.
//
/**
* Q2. 有多少小于当前数字的数字
简单
相关标签
premium lock icon
相关企业
提示
给你一个数组 nums，对于其中每个元素 nums[i]，请你统计数组中比它小的所有数字的数目。

换而言之，对于每个 nums[i] 你必须计算出有效的 j 的数量，其中 j 满足 j != i 且 nums[j] < nums[i] 。

以数组形式返回答案。



示例 1：

输入：nums = [8,1,2,2,3]
输出：[4,0,1,1,3]
解释：
对于 nums[0]=8 存在四个比它小的数字：（1，2，2 和 3）。
对于 nums[1]=1 不存在比它小的数字。
对于 nums[2]=2 存在一个比它小的数字：（1）。
对于 nums[3]=2 存在一个比它小的数字：（1）。
对于 nums[4]=3 存在三个比它小的数字：（1，2 和 2）。
示例 2：

输入：nums = [6,5,4,8]
输出：[2,1,0,3]
示例 3：

输入：nums = [7,7,7,7]
输出：[0,0,0,0]


提示：

2 <= nums.length <= 500
0 <= nums[i] <= 100
 * @return
 */

#include <stdio.h>
#include <stdlib.h>

int *global_nums;

static int compare(const void *a, const void *b) {
    return global_nums[*(int *) a] - global_nums[*(int *) b];
}

int *smallerNumbersThanCurrent(int *nums, int numsSize, int *returnSize) {
    global_nums = nums;
    *returnSize = numsSize;
    int *ans = calloc(numsSize, sizeof(int));
    int tmp[numsSize];
    int i = 0;
    for (; i < numsSize; i++)
        tmp[i] = i;
    qsort(tmp, numsSize, sizeof(int), compare);
    //开始统计
    for (i = 0; i < numsSize; i++) {
        int index = tmp[i];
        //如果前一个数与当前数不同，那前面的i个数就是答案
        if (i - 1 < 0 || nums[tmp[i - 1]] != nums[index])
            ans[index] = i;
        else
            //否则，那就只有一种情况，当前元素与前面的元素相等,那就让他等于前面元素的值
            ans[index] = ans[tmp[i - 1]];
    }
    return ans;
}

int main() {
    int arr[] = {8, 1, 2, 2, 3}, size;
    int *ans = smallerNumbersThanCurrent(arr, sizeof(arr) / sizeof(int), &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", ans[i]);
    }
    free(ans);
    return 0;
}
