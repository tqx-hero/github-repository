//
// Created by Administrator on 2026/8/15.
//
/**
* 打乱数组
给你一个整数数组 nums ，设计算法来打乱一个没有重复元素的数组。打乱后，数组的所有排列应该是 等可能 的。
实现 Solution class:
• Solution(int[] nums) 使用整数数组 nums 初始化对象
• int[] reset() 重设数组到它的初始状态并返回
• int[] shuffle() 返回数组随机打乱后的结果 
示例 1：
输入
["Solution", "shuffle", "reset", "shuffle"]
[[[1, 2, 3]], [], [], []]
输出
[null, [3, 1, 2], [1, 2, 3], [1, 3, 2]]

解释
Solution solution = new Solution([1, 2, 3]);
solution.shuffle();    // 打乱数组 [1,2,3] 并返回结果。任何 [1,2,3]的排列返回的概率应该相同。例如，返回 [3, 1, 2]
solution.reset();      // 重设数组到它的初始状态 [1, 2, 3] 。返回 [1, 2, 3]
solution.shuffle();    // 随机返回数组 [1, 2, 3] 打乱后的结果。例如，返回 [1, 3, 2]
  提示：
• 1 <= nums.length <= 50
• -106 <= nums[i] <= 106
• nums 中的所有元素都是 唯一的
• 最多可以调用 104 次 reset 和 shuffle
 * @return
 */
#include <iostream>
#include <vector>
#include <random>
using namespace std;

class Solution {
    vector<int> cache;

public:
    Solution(vector<int> &nums) : cache(nums) {
    }

    vector<int> reset() {
        return cache;
    }

    vector<int> shuffle() {
        int size = static_cast<int>(cache.size());
        vector<int> result{cache};
        if (size == 1)
            return result;
        std::random_device rd; // 真随机种子源（尽量用硬件熵）
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, size-1);
        for (int i = 0; i < size; i++)
            swap(result[dist(gen)], result[size - 1]);
        return result;
    }
};

/*
 *
*
*       int size=v.size();
        vector<int>ret(v.begin(),v.end());
        for(inti=size;i;i--)
        {
            swap(ret[random()%i],ret[i-1]);
        }
        return ret;
 *
 */

// int main() {
//     vector<int> nums{1, 2, 3};
//     Solution sl(nums);
//     const auto &shuffle = sl.shuffle();
//     std::for_each(shuffle.begin(), shuffle.end(), [](const int x) { cout << x << " "; });
//     return 0;
// }
