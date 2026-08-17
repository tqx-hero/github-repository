//
// Created by Administrator on 2026/8/17.
//
/**
* 052. 递增顺序搜索树
￼
简单
￼
相关标签
￼
相关企业
￼
给你一棵二叉搜索树，请 按中序遍历 将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。 
示例 1：
输入：
root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
输出：
[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
示例 2：
输入：
root = [5,1,7]
输出：
[1,null,5,null,7]
  提示：
• 树中节点数的取值范围是 [1, 100]
• 0 <= Node.val <= 1000
 * @return
 */
#include "../../link/TreeNode.h"

class Solution {
    void dfs(TreeNode *&cur, TreeNode *root) {
        if (!root)
            return;
        dfs(cur, root->left);
        cur->right = root;
        cur = cur->right;
        cur->left = nullptr;
        dfs(cur, root->right);
    }

public:
    TreeNode *increasingBST(TreeNode *root) {
        TreeNode sentinel(-1);
        TreeNode *node = &sentinel;
        dfs(node, root);
        return sentinel.right;
    }
};

int main() {
    return 0;
}
