//
// Created by 田庆新 on 2026/9/5.
//
/**
* 98. 验证二叉搜索树
已解答
中等
相关标签
premium lock icon
相关企业
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。

有效 二叉搜索树定义如下：

节点的左子树只包含 严格小于 当前节点的数。
节点的右子树只包含 严格大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。


示例 1：


输入：root = [2,1,3]
输出：true
示例 2：


输入：root = [5,1,4,null,null,3,6]
输出：false
解释：根节点的值是 5 ，但是右子节点的值是 4 。


提示：

树中节点数目范围在[1, 104] 内
-231 <= Node.val <= 231 - 1
 * @return
 */
#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
#include <stack>
#include <stdint.h>
using namespace std;

//TODO
class Solution {
    long long min_val = INT64_MIN;

public:
    bool isValidBST(TreeNode *root) {
        if (!root)
            return true;
        bool left_flag = isValidBST(root->left);
        if (!left_flag || min_val >= root->val)
            return false;
        min_val = root->val;
        return isValidBST(root->right);
    }
};

// int main() {
//     return 0;
// }
