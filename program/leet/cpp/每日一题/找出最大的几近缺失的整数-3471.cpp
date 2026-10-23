//
// Created by Administrator on 2026/8/18.
//
/**
* 3471. 找出最大的几近缺失整数
￼
简单
￼
相关标签
￼
相关企业
￼
提示
￼
给你一个整数数组 nums 和一个整数 k 。
如果整数 x 恰好仅出现在 nums 中的一个大小为 k 的子数组中，则认为 x 是 nums 中的几近缺失（almost missing）整数。
返回 nums 中 最大的几近缺失 整数，如果不存在这样的整数，返回 -1 。
子数组 是数组中的一个连续元素序列。 
示例 1：
输入：nums = [3,9,2,1,7], k = 3
输出：7
解释：
• 1 出现在两个大小为 3 的子数组中：[9, 2, 1]、[2, 1, 7]
• 2 出现在三个大小为 3 的子数组中：[3, 9, 2]、[9, 2, 1]、[2, 1, 7]
• 3 出现在一个大小为 3 的子数组中：[3, 9, 2]
• 7 出现在一个大小为 3 的子数组中：[2, 1, 7]
• 9 出现在两个大小为 3 的子数组中：[3, 9, 2]、[9, 2, 1]
返回 7 ，因为它满足题意的所有整数中最大的那个。
示例 2：
输入：nums = [3,9,7,2,1,7], k = 4
输出：3
解释：
• 1 出现在两个大小为 4 的子数组中：[9, 7, 2, 1]、[7, 2, 1, 7]
• 2 出现在三个大小为 4 的子数组中：[3, 9, 7, 2]、[9, 7, 2, 1]、[7, 2, 1, 7]
• 3 出现在一个大小为 4 的子数组中：[3, 9, 7, 2]
• 7 出现在三个大小为 4 的子数组中：[3, 9, 7, 2]、[9, 7, 2, 1]、[7, 2, 1, 7]
• 9 出现在两个大小为 4 的子数组中：[3, 9, 7, 2]、[9, 7, 2, 1]
返回 3 ，因为它满足题意的所有整数中最大的那个。
示例 3：
输入：nums = [0,0], k = 1
输出：-1
解释：
不存在满足题意的整数。 
提示：
• 1 <= nums.length <= 50
• 0 <= nums[i] <= 50
• 1 <= k <= nums.length
 * @return
 */
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

class Solution {
public:
    int largestInteger(vector<int> &nums, int k) {
        int buckets[51]{0}, size = static_cast<int>(nums.size()), j;
        if (size == 1)
            return nums[0];
        for (auto num: nums)
            buckets[num]++;
        //k=1或者k=n时，需要查找数组中只出现一次且最大的值
        int ret = -1;
        if (k == 1) {
            for (j = 50; j >= 0; --j) {
                if (buckets[j] == 1)
                    return j;
            }
        } else if (k == size) {
            for (j = 50; j >= 0; --j)
                if (buckets[j])
                    return j;
        } else {
            //如果1<k<n，数组除了左右边界之外都会出现在至少2个子数组中，所以可能的情况是查看左右边界，仅出现一次的较大值
            ret = buckets[nums[0]] == 1 ? nums[0] : ret;
            ret = buckets[nums[size - 1]] == 1 ? max(ret, nums[size - 1]) : ret;
        }
        return ret;
    }
};
//
// int main() {
//     vector<int> nums{0, 0};
//     int k = 2;
//     Solution sl;
//     cout << sl.largestInteger(nums, k) << endl;
//     return 0;
// }
