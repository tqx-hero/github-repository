/**
 * 3371. 识别数组中的最大异常值
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums。该数组包含 n 个元素，其中 恰好 有 n - 2 个元素是 特殊数字 。剩下的 两个 元素中，一个是所有 特殊数字 的 和 ，另一个是 异常值 。

异常值 的定义是：既不是原始特殊数字之一，也不是表示元素和的那个数。

注意，特殊数字、和 以及 异常值 的下标必须 不同 ，但可以共享 相同 的值。

返回 nums 中可能的 最大异常值。



示例 1：

输入： nums = [2,3,5,10]

输出： 10

解释：

特殊数字可以是 2 和 3，因此和为 5，异常值为 10。

示例 2：

输入： nums = [-2,-1,-3,-6,4]

输出： 4

解释：

特殊数字可以是 -2、-1 和 -3，因此和为 -6，异常值为 4。

示例 3：

输入： nums = [1,1,1,1,1,5,5]

输出： 5

解释：

特殊数字可以是 1、1、1、1 和 1，因此和为 5，另一个 5 为异常值。



提示：

3 <= nums.length <= 105
-1000 <= nums[i] <= 1000
输入保证 nums 中至少存在 一个 可能的异常值。
 */
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
// 统计数组和，遍历每个元素，把他当作异常值，用数组和减去异常值，结果就是剩余元素之和sum。
// 如果当前元素满足异常值，剩余元素之和等于2*特殊字符之和。sum/2，查看结果是否为整数并且数组中是否存在，(并且这个数不等于当前值 || (等于当前值&&个数大于1个))以此类推找出最大的异常值
// 由于需要查询元素存不存在，所以使用哈希表存储数组中的值
class Solution
{
public:
    int getLargestOutlier(vector<int> &nums)
    {
        unordered_map<int,int> cache;
        int total_sum = 0;
        for (auto num : nums)
        {
            cache[num]++;
            total_sum += num;
        }
        int exception_num = -1001;
        unordered_map<int,int>::iterator cur_it,end_it = cache.end();
        for (auto num : nums)
        {
            double sum = (total_sum - num) / 2.0;
            if (sum == static_cast<int>(sum) && (cur_it = cache.find(static_cast<int>(sum))) !=end_it && (sum != num || cur_it->second >1))
                exception_num = max(num, exception_num);
        }
        return exception_num;
    }
};

// int main()
// {
//     // vector<int> nums{-2, -1, -3, -6, 4};
//     vector<int> nums{6,-31,50,-35,41,37,-42,13};
//     Solution sl;
//     cout << sl.getLargestOutlier(nums) << endl;
//     return 0;
// }