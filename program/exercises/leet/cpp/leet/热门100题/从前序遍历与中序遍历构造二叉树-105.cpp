//
// Created by 田庆新 on 2026/9/7.
//
/**
* 105. 从前序与中序遍历序列构造二叉树
中等
相关标签
premium lock icon
相关企业
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历， inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。



示例 1:


输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]
示例 2:

输入: preorder = [-1], inorder = [-1]
输出: [-1]


提示:

1 <= preorder.length <= 3000
inorder.length == preorder.length
-3000 <= preorder[i], inorder[i] <= 3000
preorder 和 inorder 均 无重复 元素
inorder 均出现在 preorder
preorder 保证 为二叉树的前序遍历序列
inorder 保证 为二叉树的中序遍历序列
 * @return
 */
#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        unordered_map<int, int> hash_map;
        //把中序遍历的值与下标入哈希表
        //使用中序遍历下标的相对位置来确定节点的位置
        int i, size = static_cast<int>(inorder.size());
        for (i = 0; i < size; ++i)
            hash_map[inorder[i]] = i;
        auto *root = new TreeNode(preorder[0]);
        TreeNode *cur_node = root;
        stack<TreeNode *> stk;
        for (i = 1; i < size; ++i) {
            int value = preorder[i];
            auto new_node = new TreeNode(value);
            int cur_index = hash_map[value];
            //如果下标在当前节点的左边，那就是当前节点的左子树
            //挂到树上，将指针指向新的node，同时需要用栈保存cur方便回溯
            if (cur_index < hash_map[cur_node->val]) {
                cur_node->left = new_node;
                stk.push(cur_node);
            } else {
                //如果元素的下标在当前节点的右边，则需要在查看栈顶节点的下标
                //弹栈直到栈空或者当前元素下标在栈顶节点的左边
                while (!stk.empty() && cur_index > hash_map[stk.top()->val]) {
                    cur_node = stk.top();
                    stk.pop();
                }
                //cur_node为当前节点的父节点，cur_node为右子树
                cur_node->right = new_node;
            }
            cur_node = new_node;
        }
        return root;
    }
};

// int main() {
//     return 0;
// }
