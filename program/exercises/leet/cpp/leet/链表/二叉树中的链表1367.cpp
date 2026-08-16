//
// Created by Administrator on 2026/7/26.
//
/**
* 1367. 二叉树中的链表
中等
相关标签
premium lock icon
相关企业
提示
给你一棵以 root 为根的二叉树和一个 head 为第一个节点的链表。

如果在二叉树中，存在一条一直向下的路径，且每个点的数值恰好一一对应以 head 为首的链表中每个节点的值，那么请你返回 True ，否则返回 False 。

一直向下的路径的意思是：从树中某个节点开始，一直连续向下的路径。



示例 1：



输入：head = [4,2,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
输出：true
解释：树中蓝色的节点构成了与链表对应的子路径。
示例 2：



输入：head = [1,4,2,6], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
输出：true
示例 3：

输入：head = [1,4,2,6,8], root = [1,4,4,null,2,2,null,1,null,6,8,null,null,null,null,1,3]
输出：false
解释：二叉树中不存在一一对应链表的路径。


提示：

二叉树和链表中的每个节点的值都满足 1 <= node.val <= 100 。
链表包含的节点数目在 1 到 100 之间。
二叉树包含的节点数目在 1 到 2500 之间。
 * @return
 */
#include <iostream>

#include "../../link/ListNode.h"
#include "../../link/TreeNode.h"

//方法1：把递归返回条件写入子函数中
// class Solution {
// public:
//     bool isSubPath(ListNode *head, TreeNode *root) {
//         return configSubPath(head, root, head);
//     }
//
// private:
//     bool configSubPath(ListNode *head, TreeNode *root, ListNode *firstNode) {
//         if (!head)
//             return true;
//         if (!root)
//             return false;
//         if (root->val == head->val && (
//                 configSubPath(head->next, root->left, firstNode)
//                 ||
//                 configSubPath(head->next, root->right, firstNode)
//             ))
//             return true;
//         if (head == firstNode)
//             return configSubPath(head, root->left, firstNode) || configSubPath(head, root->right, firstNode);
//         return false;
//     }
// };
//方法2：在主函数判断，当不满足条件时从主函数再开始递归
class Solution {
public:
    bool isSubPath(ListNode *head, TreeNode *root) {
        if (!root)
            return false;
        return configSubPath(head, root) || isSubPath(head, root->left) || isSubPath(head, root->right);
    }

private:
    bool configSubPath(ListNode *head, TreeNode *root) {
        if (!head)
            return true;
        if (!root || root->val != head->val)
            return false;
        return configSubPath(head->next, root->left) || configSubPath(head->next, root->right);
    }
};

// int main() {
//     /*head =[1,10] root =[1,null,1,10,1,9]*/
//     // ListNode n2(10);
//     // ListNode n1(1, &n2);
//     //
//     // TreeNode t5(9);
//     // TreeNode t4(1);
//     // TreeNode t3(10, &t5, nullptr);
//     // TreeNode t2(1, &t3, &t4);
//     // TreeNode t1(1, nullptr, &t2);
//
//     // /*head =[4,2] root =[4,4,4,1,null,null,null,2]*/
//     ListNode n2(2);
//     ListNode n1(4, &n2);
//
//     TreeNode t5(2);
//     TreeNode t4(1, &t5, nullptr);
//     TreeNode t3(4);
//     TreeNode t2(4, &t4, nullptr);
//     TreeNode t1(4, &t2, &t3);
//
//     // ListNode n3(8);
//     // ListNode n2(2, &n3);
//     // ListNode n1(4, &n2);
//     //
//     // TreeNode t10(3);
//     // TreeNode t9(1);
//     // TreeNode t8(8, &t9, &t10);
//     // TreeNode t7(6);
//     // TreeNode t6(1);
//     // TreeNode t5(2, &t7, &t8);
//     // TreeNode t4(2, &t6, nullptr);
//     // TreeNode t3(4, &t5, nullptr);
//     // TreeNode t2(4, nullptr, &t4);
//     // TreeNode t1(1, &t2, &t3);
//
//     Solution sl;
//     std::cout << sl.isSubPath(&n1, &t1) << std::endl;
//
//     return 0;
// }
