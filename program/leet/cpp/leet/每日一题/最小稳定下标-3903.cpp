//
// Created by 田庆新 on 2026/9/4.
//
/**
* 3903. 最小稳定下标 I
简单
相关标签
premium lock icon
相关企业
提示
给你一个长度为 n 的整数数组 nums 和一个整数 k。

对于每个下标 i，定义它的 不稳定值 为 max(nums[0..i - 1]) - min(nums[i..n - 1])。

换句话说：

max(nums[0..i - 1]) 表示从下标 0 到下标 i - 1 的元素中的 最大值 。
min(nums[i..n - 1]) 表示从下标 i 到下标 n - 1 的元素中的 最小值 。
如果某个下标 i 的不稳定值 小于等于 k，则称该下标为 稳定下标 。

返回 最小 的稳定下标。如果不存在这样的下标，则返回 -1。



示例 1：

输入： nums = [5,0,1,4], k = 3

输出： 3

解释：

在下标 0 处：[5] 中的最大值是 5，[5, 0, 1, 4] 中的最小值是 0，因此不稳定值为 5 - 0 = 5。
在下标 1 处：[5, 0] 中的最大值是 5，[0, 1, 4] 中的最小值是 0，因此不稳定值为 5 - 0 = 5。
在下标 2 处：[5, 0, 1] 中的最大值是 5，[1, 4] 中的最小值是 1，因此不稳定值为 5 - 1 = 4。
在下标 3 处：[5, 0, 1, 4] 中的最大值是 5，[4] 中的最小值是 4，因此不稳定值为 5 - 4 = 1。
这是第一个不稳定值小于等于 k = 3 的下标，因此答案是 3。
示例 2：

输入： nums = [3,2,1], k = 1

输出： -1

解释：

在下标 0 处，不稳定值为 3 - 1 = 2。
在下标 1 处，不稳定值为 3 - 1 = 2。
在下标 2 处，不稳定值为 3 - 1 = 2。
这些值都不小于等于 k = 1，因此答案是 -1。
示例 3：

输入： nums = [0], k = 0

输出： 0

解释：

在下标 0 处，不稳定值为 0 - 0 = 0，它小于等于 k = 0。因此答案是 0。



提示：

1 <= nums.length <= 100
0 <= nums[i] <= 109
0 <= k <= 109
 * @return
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    // //1、使用2个数组，分别存储前后缀
    // int firstStableIndex(vector<int> &nums, int k) {
    //     int size = static_cast<int>(nums.size());
    //     if (size == 1)
    //         return 0;
    //     vector<int> prefix_max(size), sufix_min(size);
    //     int i;
    //     prefix_max[0] = nums[0], sufix_min[size - 1] = nums[size - 1];
    //     //找到对应位置的最大前缀
    //     for (i = 1; i < size; ++i)
    //         prefix_max[i] = max(prefix_max[i - 1], nums[i - 1]);
    //     //找对应位置的最小后缀
    //     for (i = size - 2; i >= 0; --i)
    //         sufix_min[i] = min(nums[i], sufix_min[i + 1]);
    //     //顺序遍历数组，找到第一个前缀-后缀<=k的下标
    //     for (i = 0; i < size && prefix_max[i] - sufix_min[i] > k; ++i);
    //     return i == size ? -1 : i;
    // }
    //1、优化：用一个临时数组，先倒序遍历计算后缀，再正序遍历，用一个变量记录前缀的最大数，直接计算
    int firstStableIndex(vector<int> &nums, int k) {
        int size = static_cast<int>(nums.size());
        if (size == 1)
            return 0;
        vector<int> sufix_min(size);
        int i;
        sufix_min[size - 1] = nums[size - 1];
        //找对应位置的最小后缀
        for (i = size - 2; i >= 0; --i)
            sufix_min[i] = min(nums[i], sufix_min[i + 1]);
        //顺序遍历数组，找到第一个前缀-后缀<=k的下标
        int max_prefix = nums[0];
        for (i = 0; i < size; ++i) {
            if (max_prefix - sufix_min[i] <= k)
                break;
            //更新最大前缀
            max_prefix = max(max_prefix, nums[i]);
        }
        return i == size ? -1 : i;
    }
};

// int main() {
//     return 0;
// }
