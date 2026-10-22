//
// Created by 田庆新 on 2026/8/24.
//
/**
* 1008. 前序遍历构造二叉搜索树
中等
相关标签
premium lock icon
相关企业
给定一个整数数组，它表示BST(即 二叉搜索树 )的 先序遍历 ，构造树并返回其根。

保证 对于给定的测试用例，总是有可能找到具有给定需求的二叉搜索树。

二叉搜索树 是一棵二叉树，其中每个节点， Node.left 的任何后代的值 严格小于 Node.val , Node.right 的任何后代的值 严格大于 Node.val。

二叉树的 前序遍历 首先显示节点的值，然后遍历Node.left，最后遍历Node.right。



示例 1：



输入：preorder = [8,5,1,7,10,12]
输出：[8,5,10,1,7,null,12]
示例 2:

输入: preorder = [1,3]
输出: [1,null,3]


提示：

1 <= preorder.length <= 100
1 <= preorder[i] <= 10^8
preorder 中的值 互不相同
 * @return
 */
#include <stack>

#include "../../link/TreeNode.h"
#include <vector>
using namespace std;

class Solution {
public:
    TreeNode *bstFromPreorder(vector<int> &preorder) {
        TreeNode *root;
        stack<TreeNode *> stk;
        TreeNode *head = new TreeNode(preorder[0]);
        root = head;
        stk.push(head);
        int size = static_cast<int>(preorder.size());
        for (int i = 1; i < size; i++) {
            int cur_val = preorder[i];
            TreeNode *parent = stk.top(), *cur_node = new TreeNode(cur_val);
            //往左子树遍历，都小于父节点，放到父节点的left
            if (parent->val > cur_val)
                parent->left = cur_node;
            else {
                //如果大于栈顶元素
                //表明当前元素节点必然在栈顶结点的右边，可能为右子树,所以无论如何栈顶结点的左右节点都会确定，先弹栈
                //持续比较栈顶与当前元素的值，小于当前元素时记录并弹栈，直到栈为空或者栈顶元素比当元素更大，所记录的元素即为当前节点的父节点
                //当前节点为其右子树
                while (!stk.empty() && stk.top()->val < cur_val) {
                    parent = stk.top();
                    stk.pop();
                }
                //到这里表明已经找到了当前节点的父节点parent，将其放到树上
                parent->right = cur_node;
            }
            stk.push(cur_node);
        }
        return root;
    }
};
//
// int main() {
//     return 0;
// }
