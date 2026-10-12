/**
 * 3727. 最大交替平方和
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums。你可以以任意顺序 重新排列元素 。

数组 arr 的 交替得分 定义为：

score = arr[0]2 - arr[1]2 + arr[2]2 - arr[3]2 + ...
在对 nums 重新排列后，返回其 最大可能的交替得分。



示例 1：

输入： nums = [1,2,3]

输出： 12

解释：

nums 的一种可行重排为 [2,1,3]，该排列在所有可能重排中给出了最大交替得分。

交替得分计算如下：

score = 22 - 12 + 32 = 4 - 1 + 9 = 12

示例 2：

输入： nums = [1,-1,2,-2,3,-3]

输出： 16

解释：

nums 的一种可行重排为 [-3,-1,-2,1,3,2]，该排列在所有可能重排中给出了最大交替得分。

交替得分计算如下：

score = (-3)2 - (-1)2 + (-2)2 - (1)2 + (3)2 - (2)2 = 9 - 1 + 4 - 1 + 9 - 4 = 16



提示：

1 <= nums.length <= 105
-4 * 104 <= nums[i] <= 4 * 104
 */
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;
//排序+双指针
class Solution
{
public:
    long long maxAlternatingSum(vector<int> &nums)
    {
        size_t size = nums.size();
        if (size == 1)
            return nums[0] * nums[0];
        long long ret = 0;
        sort(nums.begin(), nums.end(), [](const int &x, const int &y)
             { return abs(x) > abs(y); });
        int left, right;
        for (left = 0, right = size - 1; left < right; ++left, --right)
            ret += nums[left] * nums[left] - nums[right] * nums[right];
        if (left == right)
            ret += nums[left] * nums[left];
        return ret;
    }
};

// int main()
// {
//     // vector<int> nums{1, 2, 3};
//     vector<int> nums{1,-1,2,-2,3,-3};
//     Solution sl;
//     cout << sl.maxAlternatingSum(nums) << endl;
//     return 0;
// }