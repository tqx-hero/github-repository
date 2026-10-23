//
// Created by 田庆新 on 2026/9/4.
//
/**
* 543. 二叉树的直径
简单
相关标签
premium lock icon
相关企业
给你一棵二叉树的根节点，返回该树的 直径 。

二叉树的 直径 是指树中任意两个节点之间最长路径的 长度 。这条路径可能经过也可能不经过根节点 root 。

两节点之间路径的 长度 由它们之间边数表示。



示例 1：


输入：root = [1,2,3,4,5]
输出：3
解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
示例 2：

输入：root = [1,2]
输出：1


提示：

树中节点数目在范围 [1, 104] 内
-100 <= Node.val <= 100
 * @return
 */
#include <algorithm>

#include "../../link/TreeNode.h"
using namespace std;
//自底向上分别计算每个节点作为父节点时左右子树高度的和最大值，再在这些最大值和里面取最大的返回
class Solution {
    int max_path = 0;

    //主函数，统计每个节点作为父节点时的最大左子树深度+右子树深度，(不要忘了每个子树需要+1得到当前节点的深度)随时更新结果集max_path。
    //该函数返回的是当前节点的最大深度，即取max(左子树深度+1,右子树深度+1)
    int get_child_height(TreeNode *node) {
        if (!node)
            return -1;
        int left_height = get_child_height(node->left) + 1;
        int right_height = get_child_height(node->right) + 1;
        max_path = max(max_path, left_height + right_height);
        return max(left_height, right_height);
    }

public:
    int diameterOfBinaryTree(TreeNode *root) {
        get_child_height(root);
        return max_path;
    }
};

// int main() {
//     return 0;
// }
