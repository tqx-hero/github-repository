//
// Created by 田庆新 on 2026/9/4.
//
/**
* 226. 翻转二叉树
已解答
简单
相关标签
premium lock icon
相关企业
给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。



示例 1：



输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
示例 2：



输入：root = [2,1,3]
输出：[2,3,1]
示例 3：

输入：root = []
输出：[]


提示：

树中节点数目范围在 [0, 100] 内
-100 <= Node.val <= 100
 * @return
 */
#include <bits/move.h>

#include "../../link/TreeNode.h"
#include <algorithm>
using namespace std;

class Solution {
    void invert_node(TreeNode*node) {
        if (!node)
            return;
        auto left = node->left;
        node->left=node->right;
        node->right=left;
        invert_node(node->left);
        invert_node(node->right);
    }
public:
    TreeNode *invertTree(TreeNode *root) {
        invert_node(root);
        return root;
    }
};

// int main() {
//     return 0;
// }
