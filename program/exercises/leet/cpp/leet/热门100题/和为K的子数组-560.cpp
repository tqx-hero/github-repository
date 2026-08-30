//
// Created by 田庆新 on 2026/8/29.
//
/**
* 560. 和为 K 的子数组
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k 的子数组的个数 。

子数组是数组中元素的连续非空序列。



示例 1：

输入：nums = [1,1,1], k = 2
输出：2
示例 2：

输入：nums = [1,2,3], k = 3
输出：2


提示：

1 <= nums.length <= 2 * 104
-1000 <= nums[i] <= 1000
-107 <= k <= 107
 * @return
 */
#include <algorithm>
#include <vector>
#include <iostream>
#include <set>
#include <unordered_map>
using namespace std;

//不能使用双指针，因为存在负数的情况，需要使用前缀和
class Solution {
    // vc是升序有序数组，返回严格大于i的元素数量
    int find_cnt_bigger(vector<int> &vc, int i) {
        return static_cast<int>(vc.end() - upper_bound(vc.begin(), vc.end(), i));
    }

public:
    int subarraySum(vector<int> &nums, int k) {
        //先求前缀和，得到从第一个元素开始到当前元素累计和
        int size = static_cast<int>(nums.size()), i;
        vector<int> prefix_sum(size + 1, 0);
        prefix_sum[0] = 0;
        for (i = 1; i < size + 1; ++i)
            prefix_sum[i] = prefix_sum[i - 1] + nums[i - 1];
        //将前缀和放入哈希表，以前缀和为key，下标为value。
        //因为接下来需要根据差值计算前缀和，找到相关的下标
        //接下来还需要判断下标是否超过当前下标，小于当前下标的要舍弃
        unordered_map<int, vector<int> > cache;
        for (i = 0; i < size + 1; ++i)
            cache[prefix_sum[i]].push_back(i);
        int cnt = 0;
        //遍历前缀和，计算每个前缀和与k的差值/和，找到满足条件的前缀和
        unordered_map<int, vector<int> >::iterator bigger_iter, end_iter = cache.end();
        for (i = 0; i < size + 1; ++i) {
            int cur_value = prefix_sum[i]; //, smaller_value = cur_value - k
            //如果存在value，查找大于等于当前下标i的个数
            if ((bigger_iter = cache.find(cur_value + k)) != end_iter)
                cnt += find_cnt_bigger(bigger_iter->second, i);
        }
        return cnt;
    }
};

// int main() {
//     // vector<int> nums{100, 1, 2, 3, 4};
//     // vector<int> nums{-1, -1, 1};
//     vector<int> nums{1, -1, 0};
//     // vector<int> nums{1, 1, 1};
//     int k = 0;
//     Solution sl;
//     cout << sl.subarraySum(nums, k) << endl;
//     return 0;
// }
