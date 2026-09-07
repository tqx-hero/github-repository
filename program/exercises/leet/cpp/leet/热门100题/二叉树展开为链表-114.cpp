//
// Created by 田庆新 on 2026/9/6.
//
/**
* 114. 二叉树展开为链表
已解答
中等
相关标签
premium lock icon
相关企业
提示
给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。


示例 1：


输入：root = [1,2,5,3,4,null,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]
示例 2：

输入：root = []
输出：[]
示例 3：

输入：root = [0]
输出：[0]


提示：

树中结点数在范围 [0, 2000] 内
-100 <= Node.val <= 100


进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？
 * @return
 */
#include "../../link/TreeNode.h"
using namespace std;

//TODO
class Solution {

public:
    void flatten(TreeNode *root) {
        if (!root)
            return;
        auto left_node = root->left;
        auto right_node = root->right;
        if(left_node){
            root->right = left_node;
            TreeNode* prev = left_node;
            while(prev->right)
                prev= prev->right;
            prev->right =right_node;
            root->left =nullptr;
        }
        flatten(left_node);
        flatten(right_node);

    }
};

// int main() {
//     // TreeNode t6(6);
//     // TreeNode t5(5, nullptr, &t6);
//     // TreeNode t4(4);
//     // TreeNode t3(3);
//     // TreeNode t2(2, &t3, &t4);
//     // TreeNode t1(1, &t2, &t5);
//
//     // TreeNode t3(3);
//     // TreeNode t2(2, &t3, nullptr);
//     // TreeNode t1(1, &t2, nullptr);
//
//     TreeNode t4(4);
//     TreeNode t2(2);
//     TreeNode t3(3,&t2,&t4);
//     TreeNode t1(1,nullptr,&t3);
//     Solution sl;
//     sl.flatten(&t1);
//     return 0;
// }
