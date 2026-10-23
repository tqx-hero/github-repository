//
// Created by Administrator on 2026/8/23.
//
/**
* 1752. 检查数组是否经排序和轮转得到
简单
相关标签
premium lock icon
相关企业
提示
给你一个数组 nums 。nums 的源数组中，所有元素与 nums 相同，但按非递减顺序排列。

如果 nums 能够由源数组轮转若干位置（包括 0 个位置）得到，则返回 true ；否则，返回 false 。

源数组中可能存在 重复项 。

注意：数组 A 在轮转 x 个位置后得到长度相同的数组 B ，使得对于每一个有效的下标 i，满足 B[i] == A[(i+x) % A.length]。



示例 1：

输入：nums = [3,4,5,1,2]
输出：true
解释：[1,2,3,4,5] 为有序的源数组。
可以轮转 x = 2 个位置，使新数组从值为 3 的元素开始：[3,4,5,1,2] 。
示例 2：

输入：nums = [2,1,3,4]
输出：false
解释：源数组无法经轮转得到 nums 。
示例 3：

输入：nums = [1,2,3]
输出：true
解释：[1,2,3] 为有序的源数组。
可以轮转 x = 0 个位置（即不轮转）得到 nums 。


提示：

1 <= nums.length <= 100
1 <= nums[i] <= 100
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool check(vector<int> &nums) {
        int size = static_cast<int>(nums.size());
        if (size == 1)
            return true;
        int allow_cnt = 1, i;
        for (i = 1; i < size; ++i) {
            if (allow_cnt < 0)
                return false;
            if (nums[i] < nums[i - 1])
                allow_cnt--;
        }
        return allow_cnt == 1 || (allow_cnt == 0 && nums[0] >= nums[size - 1]);
    }
};

// int main() {
//     Solution sl;
//     vector<int> nums{5, 1, 5, 1};
//     // vector<int> nums{2,1,3,4};
//     // vector<int> nums{1,2,3};
//     // vector<int> nums{3, 4, 5, 1, 2};
//     cout << sl.check(nums) << endl;
//     return 0;
// }
