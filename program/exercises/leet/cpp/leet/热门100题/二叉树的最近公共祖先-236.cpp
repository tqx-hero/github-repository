//
// Created by 田庆新 on 2026/9/8.
//
/**
* 236. 二叉树的最近公共祖先
中等
相关标签
premium lock icon
相关企业
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”



示例 1：


输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
示例 2：


输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
示例 3：

输入：root = [1,2], p = 1, q = 2
输出：1


提示：

树中节点数目在范围 [2, 105] 内。
-109 <= Node.val <= 109
所有 Node.val 互不相同 。
p != q
p 和 q 均存在于给定的二叉树中。
 * @return
 */
#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
    TreeNode *ret = nullptr;
    unordered_set<TreeNode *> cache, target_cache;
    vector<TreeNode *> node_array;
    bool break_config = false;

    void dfs(TreeNode *node) {
        if (!node || break_config)
            return;
        node_array.push_back(node);
        //判断当前节点是否是要找的目标节点
        if (target_cache.count(node)) {
            //如果该节点是第二个节点，倒序遍历数组，找到第一个哈希表中存在的节点，即为要找的ret
            if (target_cache.size() == 1) {
                int i;
                for (i = static_cast<int>(node_array.size()) - 1; i >= 0 && !cache.count(node_array[i]); --i);
                ret = node_array[i];
                break_config = true;
                return;
            }
            //找到这个节点后，将数组经过的节点放到哈希表
            cache.insert(node_array.begin(), node_array.end());
            target_cache.erase(node);
        }
        dfs(node->left);
        while (node_array.back() != node)
            node_array.pop_back();
        dfs(node->right);
        while (node_array.back() != node)
            node_array.pop_back();
    }

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == p || root == q)
            return root;
        target_cache.emplace(p);
        target_cache.emplace(q);
        dfs(root);
        return ret;
    }
};

// int main() {
//     //root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
//     TreeNode t9(4);
//     TreeNode t8(7);
//     TreeNode t7(8);
//     TreeNode t6(0);
//     TreeNode t5(2, &t8, &t9);
//     TreeNode t4(6);
//     TreeNode t3(1, &t6, &t7);
//     TreeNode t2(5, &t4, &t5);
//     TreeNode t1(3, &t2, &t3);
//     Solution sl;
//     cout << sl.lowestCommonAncestor(&t1, &t2, &t3)->val << endl;
//     return 0;
// }
