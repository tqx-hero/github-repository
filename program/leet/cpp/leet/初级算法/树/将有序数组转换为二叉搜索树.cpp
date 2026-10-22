//
// Created by Administrator on 2026/8/13.
//
/**
* 将有序数组转换为二叉搜索树
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

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xninbt/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>

#include "../../../link/TreeNode.h"
#include <vector>
using namespace std;

class Solution {
    TreeNode *build_tree(vector<int> &nums, int left_index, int right_index) {
        if (left_index > right_index)
            return nullptr;
        //找到中间下标作为当前节点值
        int mid = left_index + (right_index - left_index) / 2;
        return new TreeNode{
            nums[mid],
            build_tree(nums, left_index, mid - 1),
            build_tree(nums, mid + 1, right_index)
        };
    }

public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return build_tree(nums, 0, nums.size() - 1);
    }
};

// int main() {
//     vector<int> nums{-10, -3, 0, 5, 9};
//     Solution sl;
//     TreeNode *tree_node = sl.sortedArrayToBST(nums);
//     while (tree_node) {
//         cout << tree_node->val << endl;
//     }
//     return 0;
// }
