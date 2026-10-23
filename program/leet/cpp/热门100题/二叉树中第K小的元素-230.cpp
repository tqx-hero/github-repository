//
// Created by 田庆新 on 2026/9/6.
//
/**
* 230. 二叉搜索树中第 K 小的元素
中等
相关标签
premium lock icon
相关企业
提示
给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（k 从 1 开始计数）。



示例 1：


输入：root = [3,1,4,null,2], k = 1
输出：1
示例 2：


输入：root = [5,3,6,2,4,null,null,1], k = 3
输出：3




提示：

树中的节点数为 n 。
1 <= k <= n <= 104
0 <= Node.val <= 104


进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k 小的值，你将如何优化算法？
 * @return
 */
#include "../../link/TreeNode.h"

class Solution {
    int ret = -1;

    void dfs(TreeNode *node, int &k) {
        if (!node)
            return;
        dfs(node->left, k);
        if (k == 0)
            return;
        ret = node->val;
        --k;
        dfs(node->right, k);
    }

public:
    int kthSmallest(TreeNode *root, int k) {
        dfs(root, k);
        return ret;
    }
};

// int main() {
//     return 0;
// }
