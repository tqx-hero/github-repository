//
// Created by 田庆新 on 2026/8/26.
//
/**
* 128. 最长连续序列
中等
相关标签
premium lock icon
相关企业
给定一个未排序的整数数组 nums ，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现时间复杂度为 O(n) 的算法解决此问题。



示例 1：

输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
示例 2：

输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
示例 3：

输入：nums = [1,0,1,2]
输出：3


提示：

0 <= nums.length <= 105
-109 <= nums[i] <= 109
 * @return
 */
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
    //并查集压缩算法
    int find_max(unordered_map<int, pair<int, int> > &buckets, int key) {
        int bigger = buckets[key].first;
        //找到最大值，当且仅当key与最大值相等时停止
        if (key == bigger)
            return key;
        //如果不相等，说明有更大的，需要继续找
        //找到后更新沿途所有节点最大值
        return buckets[key].first = find_max(buckets, bigger);
    }

    int find_min(unordered_map<int, pair<int, int> > &buckets, int key) {
        int smaller = buckets[key].second;
        //找到最大值，当且仅当key与最大值相等时停止
        if (key == smaller)
            return key;
        //如果不相等，说明有更大的，需要继续找
        //找到后更新沿途所有节点最大值
        return buckets[key].second = find_min(buckets, smaller);
    }

public:
    int longestConsecutive(vector<int> &nums) {
        //定义并查集,存放当前元素记录的连续区域的最大值，最小值
        //value是一个数对，分别存放：<cur_max,cur_min>
        unordered_map<int, pair<int, int> > buckets;
        int largest_len = 0;
        for (int nu: nums) {
            //如果桶内已经存在该元素，直接舍弃
            if (buckets.count(nu))
                continue;
            //不存在，则初始化元素的最大最小值
            buckets[nu].first = buckets[nu].second = nu;
            //判断当前元素上一个值是否存在
            //如果存在，那必然存在buckets[nu+1] =nu+1
            //因为到这里nu不存在，nu+1所在的连续序列必然没有nu，所以它的最小值一定为它自身nu+1,此时设置nu+1的最小值为当前值nu
            //并查集查找最大值并赋值给buckets[nu].max
            if (buckets.count(nu + 1)) {
                buckets[nu].first = find_max(buckets, nu + 1);
                buckets[nu + 1].second = buckets[nu].second;
            }
            //接下来就要设置nu的最小值，查看nu-1是否存在
            if (buckets.count(nu - 1)) {
                //同样，如果nu-1存在,那必然buckets[nu-1]=nu-1
                //设置buckets[nu-1].max=nu;
                //buckets[nu].min同样用并查集算法查找;
                buckets[nu].second = find_min(buckets, nu - 1);
                buckets[nu - 1].first = buckets[nu].first;
            }
            //计算它的最大最小值区间，更新ret
            largest_len = max(buckets[nu].first - buckets[nu].second + 1, largest_len);
        }
        return largest_len;
    }
};

// int main() {
//     vector<int> nums{};
//     // vector<int> nums{0,3,7,2,5,8,4,6,0,1};
//     // vector<int> nums{100, 4, 200, 1, 3, 2};
//     Solution sl;
//     cout << sl.longestConsecutive(nums) << endl;
//     return 0;
// }
