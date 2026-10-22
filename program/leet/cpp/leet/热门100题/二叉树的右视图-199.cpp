//
// Created by 田庆新 on 2026/9/6.
//
/**
* 199. 二叉树的右视图
中等
相关标签
premium lock icon
相关企业
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。



示例 1：

输入：root = [1,2,3,null,5,null,4]

输出：[1,3,4]

解释：



示例 2：

输入：root = [1,2,3,4,null,null,null,5]

输出：[1,3,4,5]

解释：



示例 3：

输入：root = [1,null,3]

输出：[1,3]

示例 4：

输入：root = []

输出：[]



提示:

二叉树的节点个数的范围是 [0,100]
-100 <= Node.val <= 100
 * @return
 */

#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> rightSideView(TreeNode *root) {
        vector<int> ret;
        if (!root)
            return ret;
        queue<TreeNode*> cache;
        cache.push(root);
        int size;
        while ((size = static_cast<int>(cache.size())) !=0) {
            while (size--) {
                //只拿去最右边的那个节点的value，放入ret
                auto tree_node = cache.front();
                if (tree_node->left)
                    cache.push(tree_node->left);
                if (tree_node->right)
                    cache.push(tree_node->right);
                if (size ==0)
                    ret.push_back(tree_node->val);
                cache.pop();
            }
        }
        return ret;
    }
};
//
// int main() {
//     return 0;
// }
