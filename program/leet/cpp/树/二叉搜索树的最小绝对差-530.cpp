/**
 *530. 二叉搜索树的最小绝对差
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

树中节点的数目范围是 [2, 104]
0 <= Node.val <= 105
 

注意：本题与 783 https://leetcode.cn/problems/minimum-distance-between-bst-nodes/ 相同
 */
#include <iostream>
#include "../tree/TreeNode.h"
using namespace std;

class Solution {
	int before_val = -1,min_sub = 1 << 30;

	void dfs(TreeNode* root){
		if(!root)
			return;
		dfs(root->left);
		//中序遍历
		if(before_val != -1)
			min_sub = min(min_sub,root->val - before_val);
		before_val = root->val;
		dfs(root->right);
	}
public:
    int getMinimumDifference(TreeNode* root) {
	    dfs(root);
	    return min_sub;
    }
};

int main(){
	TreeNode node6{6};
	TreeNode node3{3};
	TreeNode node1{1};
	TreeNode node2{2,&node1,&node3};
	TreeNode node4{4,&node2,&node6};
	Solution sl;
	cout << sl.getMinimumDifference(&node4) << endl;
	return 0;
}
