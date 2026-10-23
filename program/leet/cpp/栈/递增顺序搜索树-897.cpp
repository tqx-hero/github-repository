//
// Created by Administrator on 2026/8/6.
//
/**
* 897. 递增顺序搜索树
简单
相关标签
premium lock icon
相关企业
给你一棵二叉搜索树的 root ，请你 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。



示例 1：


输入：root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
示例 2：


输入：root = [5,1,7]
输出：[1,null,5,null,7]


提示：

树中节点数的取值范围是 [1, 100]
0 <= Node.val <= 1000
 * @return
 */
#include "../../link/TreeNode.h"

class Solution {
    void dfs(TreeNode *root, TreeNode *&cur) {
        if (!root)
            return;
        dfs(root->left, cur);
        cur->right = root;
        cur = cur->right;
        cur->left = nullptr;
        dfs(root->right, cur);
    }

public:
    TreeNode *increasingBST(TreeNode *root) {
        TreeNode sentinel = TreeNode(-1);
        TreeNode *dummyNode = &sentinel;
        dfs(root, dummyNode);
        return sentinel.right;
    }
};

// int main() {
//     /*[2,1,4,null,null,3]*/
//     TreeNode t3(3);
//     TreeNode t1(1);
//     TreeNode t4(4, &t3, nullptr);
//     TreeNode t2(2, &t1, &t4);
//     Solution sl;
//     const auto & tree_node = sl.increasingBST(&t2);
//
//     return 0;
// }
