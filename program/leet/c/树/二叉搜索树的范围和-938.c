/**
938. 二叉搜索树的范围和
简单
相关标签
premium lock icon
相关企业
给定二叉搜索树的根结点 root，返回值位于范围 [low, high] 之间的所有结点的值的和。

 

示例 1：


输入：root = [10,5,15,3,7,null,18], low = 7, high = 15
输出：32
示例 2：


输入：root = [10,5,15,3,7,13,18,1,null,6], low = 6, high = 10
输出：23
 

提示：

树中节点数目在范围 [1, 2 * 104] 内
1 <= Node.val <= 105
1 <= low <= high <= 105
所有 Node.val 互不相同
  */
#include "../tree/treenode.h"
#include <stdio.h>
typedef struct TreeNode TreeNode;

void dfs(TreeNode *root,int low,int high,int *sump){
	if(!root)
		return;
	dfs(root->left,low,high,sump);
	if(root->val >= low && root->val <= high)
		*sump += root->val;
	else if(root->val > high)
		return;
	dfs(root->right,low,high,sump);
}

int rangeSumBST(struct TreeNode* root, int low, int high) {
	int sum = 0;
	dfs(root,low,high,&sum);
	return sum;
}

int main(){
	return 0;
}
