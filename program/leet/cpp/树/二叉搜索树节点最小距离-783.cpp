/**
  783. 二叉搜索树节点最小距离
简单
相关标签
premium lock icon
相关企业
给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。

差值是一个正数，其数值等于两值之差的绝对值。



示例 1：


输入：root = [4,2,6,1,3]
输出：1
示例 2：


输入：root = [1,0,48,null,null,12,49]
输出：1


提示：

树中节点的数目范围是 [2, 100]
0 <= Node.val <= 105
  */
#include "../tree/TreeNode.h"
#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {

    int prev = -1,min_sub = INT_MAX;

    void dfs(TreeNode* root){
	if(!root)
	    return;
	dfs(root->left);
	if(prev >= 0)
	    min_sub = std::min(min_sub,root->val - prev);
	prev = root->val;
	dfs(root->right);
    }

public:
    int minDiffInBST(TreeNode* root) {
	dfs(root);
	return min_sub;
    }
};

int main(){
	return 0;
}
