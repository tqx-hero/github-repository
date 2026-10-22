//
// Created by 田庆新 on 2026/9/5.
//
/**
* 108. 将有序数组转换为二叉搜索树
已解答
简单
相关标签
premium lock icon
相关企业
给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 平衡 二叉搜索树。



示例 1：


输入：nums = [-10,-3,0,5,9]
输出：[0,-3,9,-10,null,5]
解释：[0,-10,5,null,-3,null,9] 也将被视为正确答案：

示例 2：


输入：nums = [1,3]
输出：[3,1]
解释：[1,null,3] 和 [3,1] 都是高度平衡二叉搜索树。


提示：

1 <= nums.length <= 104
-104 <= nums[i] <= 104
nums 按 严格递增 顺序排列
 * @return
 */
#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    TreeNode *build_tree(vector<int> &nums, int left, int right) {
        if (left > right)
            return nullptr;
        int mid = left + (right - left) / 2;
        return new TreeNode(nums[mid], build_tree(nums, left, mid - 1),
                            build_tree(nums, mid + 1, right));
    }

public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        int size = static_cast<int>(nums.size());
        //根取中间值，左右子树的根分别取左右区间的中间值，以此类推
        return size == 1 ? new TreeNode(nums[0]) : build_tree(nums, 0, size - 1);
    }
};

// int main() {
//     return 0;
// }
