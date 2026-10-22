//
// Created by 田庆新 on 2026/8/31.
//
/**
* 238. 除了自身以外数组的乘积
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除了 nums[i] 之外其余各元素的乘积 。

题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位 整数范围内。

请 不要使用除法，且在 O(n) 时间复杂度内完成此题。



示例 1:

输入: nums = [1,2,3,4]
输出: [24,12,8,6]
示例 2:

输入: nums = [-1,1,0,-3,3]
输出: [0,0,9,0,0]


提示：

2 <= nums.length <= 105
-30 <= nums[i] <= 30
输入 保证 数组 answer[i] 在  32 位 整数范围内


进阶：你可以在 O(1) 的额外空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组 不被视为 额外空间。）
 * @return
 */
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;
//1、动态规划，两个数组分别记录每个位置的前缀乘积与后缀乘积，分别相乘得出结果
// class Solution {
// public:
//     vector<int> productExceptSelf(vector<int> &nums) {
//         int size = static_cast<int>(nums.size());
//         //初始化各个位置的前后缀乘积
//         vector<int> prefix_mul(size, 1), sufix_mul(size, 1);
//         int i;
//         //从第二个位置开始计算前缀乘积
//         for (i = 1; i < size; i++)
//             prefix_mul[i] = prefix_mul[i - 1] * nums[i - 1];
//         //从后往前计算后缀乘积
//         for (i = size - 2; i >= 0; --i)
//             sufix_mul[i] = sufix_mul[i + 1] * nums[i + 1];
//         //前缀积*后缀积
//         vector<int> ret;
//         ret.resize(size);
//         for (i = 0; i < size; ++i)
//             ret[i] = prefix_mul[i] * sufix_mul[i];
//         return ret;
//     }
// };
//2、改进，直接使用ret结果数组存放前缀积，在倒序遍历计算后缀积的同时直接乘入ret，即可省略生成2个数组的空间
//同时还需要注意用一个变量来记录后一位下标的后缀积，供前面下标的数据运算
class Solution {
public:
    vector<int> productExceptSelf(vector<int> &nums) {
        int size = static_cast<int>(nums.size());
        int i;
        vector<int> ret(size, 1);
        //从第二个位置开始计算前缀乘积
        for (i = 1; i < size; i++)
            ret[i] = ret[i - 1] * nums[i - 1];
        //从后往前计算后缀乘积
        int sufix_mul = 1;
        //前缀积*后缀积
        for (i = size - 1; i >= 0; --i) {
            ret[i] *= sufix_mul;
            //更新后缀积：
            sufix_mul *= nums[i];
        }
        return ret;
    }
};

// int main() {
//     vector<int> nums{-1, 1, 0, -3, 3};
//     Solution sl;
//     const auto &except_self = sl.productExceptSelf(nums);
//     for_each(except_self.begin(), except_self.end(), [](const int x) { cout << x << " "; });
//     return 0;
// }
