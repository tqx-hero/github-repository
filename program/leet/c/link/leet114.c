//
// Created by Administrator on 2026/6/3.
//
/**
*
￼
代码
￼
测试用例
测试用例
￼
测试结果
114. 二叉树展开为链表
￼
中等
￼
相关标签
￼
相关企业
￼
提示
￼
给你二叉树的根结点 root ，请你将它展开为一个单链表：
• 展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
• 展开后的单链表应该与二叉树 先序遍历 顺序相同。 
示例 1：
输入：
root = [1,2,5,3,4,null,6]
输出：
[1,null,2,null,3,null,4,null,5,null,6]
示例 2：
输入：
root = []
输出：
[]
示例 3：
输入：
root = [0]
输出：
[0]
  提示：
• 树中结点数在范围 [0, 2000] 内
• -100 <= Node.val <= 100 
进阶：你可以使用原地算法（O(1) 额外空间）展开这棵树吗？
 * @return
 */
#include <stdio.h>

#include "../node/treenode.h"
#define TREENODE struct TreeNode*

void flatten(struct TreeNode *root) {
    if (!root)
        return;
    TREENODE left = root->left;
    TREENODE right = root->right;
    //左子树存在，
    if (left) {
        root->left = NULL;
        root->right = left;
        TREENODE prev = left;
        //找到最右边的叶子结点
        while (prev->right) {
            prev = prev->right;
        }
        prev->right = right;
    }
    flatten(left);
    flatten(right);
}

typedef struct TreeNode TreeNode;

// int main() {
//     TreeNode t6= {6,NULL,NULL};
//     TreeNode t5= {5,NULL,&t6};
//     TreeNode t4= {4,NULL,NULL};
//     TreeNode t3= {3,NULL,NULL};
//     TreeNode t2= {2,&t3,&t4};
//     TreeNode t1= {1,&t2,&t5};
//     flatten(&t1);
//
//     return 0;
// }
