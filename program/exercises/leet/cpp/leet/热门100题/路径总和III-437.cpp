//
// Created by 田庆新 on 2026/9/8.
//
/**
* 437. 路径总和 III
中等
相关标签
premium lock icon
相关企业
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。

路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。



示例 1：



输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
示例 2：

输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3


提示:

二叉树的节点个数的范围是 [0,1000]
-109 <= Node.val <= 109
-1000 <= targetSum <= 1000
 * @return
 */
#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;
class Solution {
    struct TreeNodeWrapper {
        TreeNode *node;
        bool visited;

        TreeNodeWrapper(TreeNode *node, bool visited = false)
            : node(node),
              visited(visited) {
        }
    };

public:
    int pathSum(TreeNode *root, int targetSum) {
        //前缀和缓存，存放键值对<前缀和,前缀和累计出现次数>
        long long cur_prefix = 0;
        unordered_map<long long, int> prefix_cache;
        prefix_cache[0] = 1;
        stack<TreeNodeWrapper *> node_cache;
        int ret = 0;
        //前序遍历，入栈同时计算前缀和放到哈希表记录
        unordered_map<long long, int>::iterator it, end_it = prefix_cache.end();
        TreeNode *cur_node = root;
        while (cur_node || !node_cache.empty()) {
            if (cur_node) {
                cur_prefix += cur_node->val;
                //计算出的前缀和，再查找哈希表中是否存在当前前缀和-targetNum，如果存在，添加上value(value记录次数)
                if ((it = prefix_cache.find(cur_prefix - targetSum)) != end_it)
                    ret += it->second;
                //前缀和入哈希表
                prefix_cache[cur_prefix]++;
                //节点入栈，方便回溯
                node_cache.push(new TreeNodeWrapper(cur_node));
                cur_node = cur_node->left;
                continue;
            }
            //如果节点为空，说明已经到头了,这时需要回溯。
            //需要查看栈顶节点是否有右子树，如果有，就继续遍历压栈
            auto top_node = node_cache.top();
            if (top_node->node->right && !top_node->visited) {
                cur_node = top_node->node->right;
                top_node->visited = true;
            } else {
                //如果不存在右子树，那就弹栈，弹栈的同时令当前前缀和的累计次数-1
                if (--prefix_cache[cur_prefix] == 0)
                    prefix_cache.erase(cur_prefix);
                cur_prefix -= top_node->node->val;
                node_cache.pop();
                delete top_node;
            }
        }
        return ret;
    }
};

// int main() {
//     //root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
//     TreeNode t9(1);
//     TreeNode t8(-2);
//     TreeNode t7(3);
//     TreeNode t6(11);
//     TreeNode t5(2, nullptr, &t9);
//     TreeNode t4(3, &t7, &t8);
//     TreeNode t3(-3, nullptr, &t6);
//     TreeNode t2(5, &t4, &t5);
//     TreeNode t1(10, &t2, &t3);
//     int targetSum = 8;
//     Solution sl;
//     cout << sl.pathSum(&t1, targetSum) << endl;
//     return 0;
// }
