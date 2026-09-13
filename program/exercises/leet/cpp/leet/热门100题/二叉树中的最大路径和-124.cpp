/**
 * 124. 二叉树中的最大路径和
困难
相关标签
premium lock icon
相关企业
二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。

 

示例 1：


输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
示例 2：


输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
提示：

树中节点数目范围是 [1, 3 * 104]
-1000 <= Node.val <= 1000
 */
#include "../../link/TreeNode.h"
#include <algorithm>
#include <iostream>
using namespace std;
class Solution {
    int ret=INT_MIN;
    int maxPathSumHelper(TreeNode* root){
        //如果该节点为叶子节点，直接返回它本身的值
        if(!root)
            return 0;
        //如果节点有子节点，需要递归计算子树的最优路径值
        int cur_ret=root->val,left_ret = 0,right_ret =0;
        left_ret = max(maxPathSumHelper(root->left),0);
        right_ret =max(maxPathSumHelper(root->right),0);
        ret = max(ret,cur_ret+left_ret+right_ret);
        return cur_ret+max(left_ret,right_ret);
    }
public:
    int maxPathSum(TreeNode* root) {
        maxPathSumHelper(root);
        return ret;
    }
};

// int main(){
//     return 0;
// }