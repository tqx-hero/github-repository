//
// Created by 田庆新 on 2026/9/4.
//
/**
*94. 二叉树的中序遍历
已解答
简单
相关标签
premium lock icon
相关企业
给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。



示例 1：


输入：root = [1,null,2,3]
输出：[1,3,2]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [1]
输出：[1]


提示：

树中节点数目在范围 [0, 100] 内
-100 <= Node.val <= 100


进阶: 递归算法很简单，你可以通过迭代算法完成吗？
 * @return
 */
#include <stack>
#include <vector>
#include "../../link/TreeNode.h"
using namespace std;

class Solution {
public:
    vector<int> inorderTraversal(TreeNode *root) {
        stack<TreeNode *> cache;
        vector<int> ret;
        TreeNode *cur = root;
        while (cur || !cache.empty()) {
            if (cur) {
                //如果当前节点存在，将其压入栈内
                cache.push(cur);
                cur = cur->left;
            } else {
                //cur不存在了，取出栈顶
                auto tree_node = cache.top();
                ret.push_back(tree_node->val);
                cache.pop();
                cur = tree_node->right;
            }
        }
        return ret;
    }
};

// int main() {
//     return 0;
// }
