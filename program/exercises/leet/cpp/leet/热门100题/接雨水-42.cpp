//
// Created by Administrator on 2026/8/31.
//
/**
* 42. 接雨水
已解答
困难
相关标签
premium lock icon
相关企业
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。



示例 1：



输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
示例 2：

输入：height = [4,2,0,3,2,5]
输出：9


提示：

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int> &height) {
        //分别记录每个下标位置的左右最大值，如果最大值小于等于当前柱子值，那这个单位的必然存不住水
        int size = static_cast<int>(height.size()), ret = 0;
        if (size == 1)
            return ret;
        vector<int> left_max(size, 0), right_max(size, 0);
        left_max[0] = height[0];
        int i = 1;
        for (; i < size; ++i)
            left_max[i] = max(left_max[i - 1], height[i]);
        right_max[size - 1] = height[size - 1];
        for (i = size - 2; i >= 0; --i)
            right_max[i] = max(right_max[i + 1], height[i]);
        for (i = 1; i < size; ++i)
            //只有左右均大于当前柱子高度，计算当前下标存储的水
            ret += min(left_max[i], right_max[i]) - height[i];
        return ret;
    }
};

// int main() {
//     vector<int> height{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
//     Solution sl;
//     cout << sl.trap(height) << endl;
//     return 0;
// }
