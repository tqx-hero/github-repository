//
// Created by Administrator on 2026/7/15.
//
/**
* 面试题 04.03. 特定深度节点链表
中等
相关标签
premium lock icon
相关企业
提示
给定一棵二叉树，设计一个算法，创建含有某一深度上所有节点的链表（比如，若一棵树的深度为 D，则会创建出 D 个链表）。返回一个包含所有深度的链表的数组。



示例：

输入：[1,2,3,4,5,null,7,8]

        1
       /  \
      2    3
     / \    \
    4   5    7
   /
  8

输出：[[1],[2,3],[4,5,7],[8]]
 * @return
 */
#include <queue>

#include "../link/ListNode.h"
#include "../link/TreeNode.h"
#include <vector>
using namespace std;

class Solution {
public:
    vector<ListNode *> listOfDepth(TreeNode *tree) {
        vector<ListNode *> list;
        if (!tree)
            return list;
        queue<TreeNode *> queue;
        queue.push(tree);
        ListNode sentinel(0);
        while (!queue.empty()) {
            ListNode *cur = &sentinel;
            int count = queue.size();
            for (int i = 0; i < count; i++) {
                auto tree_node = queue.front();
                cur->next = new ListNode(tree_node->val);
                cur = cur->next;
                queue.pop();
                if (tree_node->left)
                    queue.push(tree_node->left);
                if (tree_node->right)
                    queue.push(tree_node->right);
            }
            list.push_back(sentinel.next);
        }
        return list;
    }
};

// int main() {
//     return 0;
// }
