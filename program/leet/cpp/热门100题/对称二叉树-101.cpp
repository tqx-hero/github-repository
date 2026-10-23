//
// Created by 田庆新 on 2026/9/4.
//
/**
* 101. 对称二叉树
已解答
简单
相关标签
premium lock icon
相关企业
给你一个二叉树的根节点 root ， 检查它是否轴对称。



示例 1：


输入：root = [1,2,2,3,4,4,3]
输出：true
示例 2：


输入：root = [1,2,2,null,3,null,3]
输出：false


提示：

树中节点数目在范围 [1, 1000] 内
-100 <= Node.val <= 100


进阶：你可以运用递归和迭代两种方法解决这个问题吗？
 * @return
 */
#include <stack>

#include "../../link/TreeNode.h"
using namespace std;
// //用递归实现
// class Solution {
//     bool check_two_node(TreeNode *left, TreeNode *right) {
//         if (!left && !right)
//             return true;
//         if (!left || !right || left->val != right->val)
//             return false;
//         return check_two_node(left->left,right->right) &&
//             check_two_node(left->right,right->left);
//     }
//
// public:
//     bool isSymmetric(TreeNode *root) {
//         return check_two_node(root->left,root->right);
//     }
// };
//用栈实现
class Solution {
public:
    bool isSymmetric(TreeNode *root) {
        if (!root->left && !root->right)
            return true;
        if (!root->left || !root->right)
            return false;
        stack<TreeNode *> cache;
        cache.push(root->right);
        cache.push(root->left);
        while (!cache.empty()) {
            auto t1 = cache.top();
            cache.pop();
            auto t2 = cache.top();
            cache.pop();
            if (
                (t1->val != t2->val)
                ||
                (!t1->left && t2->right) || (!t2->right && t1->left)
                ||
                (!t1->right && t2->left) || (!t2->left && t1->right)
            )
                return false;
            if (t1->left) {
                cache.push(t2->right);
                cache.push(t1->left);
            }
            if (t1->right) {
                cache.push(t2->left);
                cache.push(t1->right);
            }
        }
        return true;
    }
};

// int main() {
//     return 0;
// }
