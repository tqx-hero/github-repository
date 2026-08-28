//
// Created by 田庆新 on 2026/8/28.
//
/**
* 15. 三数之和
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。请你返回所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。





示例 1：

输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
示例 2：

输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
示例 3：

输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。


提示：

3 <= nums.length <= 3000
-105 <= nums[i] <= 105
 * @return
 */
#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

class Solution {
    struct compared {
        bool operator()(const vector<int> &v1, const vector<int> &v2) const {
            if (v1[0] != v2[0])
                return v1[0] < v2[0];
            if (v1[1] != v2[1])
                return v1[1] < v2[1];
            return v1[2] < v2[2];
        }
    };

public:
    vector<vector<int> > threeSum(vector<int> &nums) {
        int zero_cnt = 0;
        unordered_map<int, int> negative_cache, positive_cache;
        set<vector<int>, compared> prune_set;
        //统计数出现次数
        for (int num: nums) {
            if (num > 0)
                positive_cache[num]++;
            else if (num < 0)
                negative_cache[num]++;
            else
                zero_cnt++;
        }
        //如果超过3个0，先把3个0统计出来
        if (zero_cnt >= 3)
            prune_set.emplace(vector{0, 0, 0});
        for (auto &ne_iter: negative_cache) {
            int ne_value = ne_iter.first;
            for (auto &po_iter: positive_cache) {
                int po_value = po_iter.first;
                int add_two = -(ne_value + po_value);
                if (
                    (add_two == 0 && zero_cnt) //两数之和等于0且0存在
                    ||
                    (add_two > 0 && ((add_two == po_value && po_iter.second > 1) || (
                                         add_two != po_value && positive_cache.count(add_two))))
                    ||
                    (add_two < 0 && ((add_two == ne_value && ne_iter.second > 1) ||
                                     (add_two != ne_value && negative_cache.count(add_two))))
                ) {
                    //大于0，如果两数之和等于po_value且po_value数量大于2个 && 不等于po_value且哈希表中存在，都满足条件，是有效的三元组
                    //还需要放入一个数据结构去重
                    vector<int> candidate{ne_value, add_two, po_value};
                    sort(candidate.begin(), candidate.end());
                    if (prune_set.count(candidate) == 0)
                        prune_set.emplace(candidate);
                }
            }
        }
        return vector<vector<int> >{prune_set.begin(), prune_set.end()};
    }
};

// int main() {
//     // vector<int> nums = {-1, 0,  2};
//     vector<int> nums = {-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4};
//     // vector<int> nums = {-1, 0, 1, 2, -1, -4};
//     Solution sl;
//     const auto &three_sum = sl.threeSum(nums);
//     for_each(three_sum.begin(), three_sum.end(), [](const vector<int> &x) {
//         for_each(x.begin(), x.end(), [](const int x) { cout << x << " "; });
//         cout << endl;
//     });
//     return 0;
// }
