//
// Created by Administrator on 2026/7/15.
//
/**
*面试题 17.12. BiNode
简单
相关标签
premium lock icon
相关企业
提示
二叉树数据结构TreeNode可用来表示单向链表（其中left置空，right为下一个链表节点）。实现一个方法，把二叉搜索树转换为单向链表，要求依然符合二叉搜索树的性质，转换操作应是原址的，也就是在原始的二叉搜索树上直接修改。

返回转换后的单向链表的头节点。

注意：本题相对原题稍作改动



示例：

输入： [4,2,5,1,3,null,6,0]
输出： [0,null,1,null,2,null,3,null,4,null,5,null,6]
提示：

节点数量不会超过 100000。
 * @return
 */
#include "../link/TreeNode.h"
#include <iostream>
using namespace std;

class Solution {
    TreeNode *head, *cur;

public:
    void transfer(TreeNode *treeNode) {
        if (!treeNode)
            return;
        transfer(treeNode->left);
        cur->right = treeNode;
        cur = treeNode;
        treeNode->left = nullptr;
        transfer(treeNode->right);
    }

    TreeNode *convertBiNode(TreeNode *root) {
        TreeNode tr(0, nullptr, root);
        cur = head = &tr;
        transfer(root);
        return head->right;
    }
};

// int main() {
//     TreeNode t7(0);
//     TreeNode t6(6);
//     TreeNode t5(3);
//     TreeNode t4(1, &t7, nullptr);
//     TreeNode t3(5, nullptr, &t6);
//     TreeNode t2(2, &t4, &t5);
//     TreeNode t1(4, &t2, &t3);
//     Solution sl;
//     auto node = sl.convertBiNode(&t1);
//     while (node) {
//         cout << node->val << endl;
//         node = node->right;
//     }
//     return 0;
// }
