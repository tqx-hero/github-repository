//
// Created by Administrator on 2026/7/15.
//

#ifndef CPP_TREENODE_H
#define CPP_TREENODE_H


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode();

    TreeNode(int x);

    TreeNode(int x, TreeNode *left, TreeNode *right);
};


#endif //CPP_TREENODE_H
