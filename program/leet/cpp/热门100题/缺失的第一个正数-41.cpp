//
// Created by 田庆新 on 2026/9/1.
//
/**
* 41. 缺失的第一个正数
困难
相关标签
premium lock icon
相关企业
提示
给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。

请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。


示例 1：

输入：nums = [1,2,0]
输出：3
解释：范围 [1,2] 中的数字都在数组中。
示例 2：

输入：nums = [3,4,-1,1]
输出：2
解释：1 在数组中，但 2 没有。
示例 3：

输入：nums = [7,8,9,11,12]
输出：1
解释：最小的正数 1 没有出现。


提示：

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
 * @return
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int> &nums) {
        int size = static_cast<int>(nums.size()), i;
        //第一遍先把所有非正数改成[1,size]范围之外的数
        for (i = 0; i < size; ++i) {
            //如果数为非正数
            if (nums[i] <= 0)
                nums[i] = size + 1;
        }
        //第二遍再把所有下标所在的值，以他作为第n个元素把对应下标变为负数，算是打上存在的标记
        //注意，可能会有重复元素，所以需要判断所在下标值是否为负数，负数就不需要变了
        for (i = 0; i < size; ++i) {
            int temp_index;
            if ((temp_index = abs(nums[i])) <= size && nums[temp_index - 1] > 0)
                nums[temp_index - 1] = -nums[temp_index - 1];
        }
        //再次遍历，直到找到第一个正数，所在的index+1即为第二次遍历打上的数的值，返回下标+1即可
        for (i = 0; i < size && nums[i] < 0; ++i);
        return i + 1;
    }
};

// int main() {
//     vector<int> nums{7,8,9,11,12};
//     // vector<int> nums{3, 4, -1, 1};
//     Solution sl;
//     cout << sl.firstMissingPositive(nums) << endl;
//     return 0;
// }
