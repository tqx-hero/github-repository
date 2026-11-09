/**
1022. 从根到叶的二进制数之和
简单
相关标签
premium lock icon
相关企业
提示
给出一棵二叉树，其上每个结点的值都是 0 或 1 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数。

例如，如果路径为 0 -> 1 -> 1 -> 0 -> 1，那么它表示二进制数 01101，也就是 13 。
对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字。

返回这些数字之和。题目数据保证答案是一个 32 位 整数。

 

示例 1：


输入：root = [1,0,1,0,1,0,1]
输出：22
解释：(100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
示例 2：

输入：root = [0]
输出：0
 

提示：

树中的节点数在 [1, 1000] 范围内
Node.val 仅为 0 或 1 
  */
#include "../tree/treenode.h"
#include <stdio.h>
#include <stdlib.h>

void dfs(struct TreeNode *root,int *total_sum,int cur_sum){
	if(!root)
		return;
	//如果节点不为空，将原来的值左移,添加当前值
	cur_sum = (cur_sum << 1) + root->val;
	if(!root->left && !root->right)
		*total_sum += cur_sum; 
	dfs(root->left,total_sum,cur_sum);
	dfs(root->right,total_sum,cur_sum);
}

int sumRootToLeaf(struct TreeNode* root) {
	int total_sum = 0,cur_sum = 0;
	dfs(root,&total_sum,cur_sum);
	return total_sum;
}

int main(){
	//root = [1,0,1,0,1,0,1]
	struct TreeNode t7= {1,NULL,NULL};
	struct TreeNode t6= {0,NULL,NULL};
	struct TreeNode t5= {1,NULL,NULL};
	struct TreeNode t4= {0,NULL,NULL};
	struct TreeNode t3= {1,&t6,&t7};
	struct TreeNode t2= {0,&t4,&t5};
	struct TreeNode t1= {1,&t2,&t3};
	fprintf(stdout,"%d\n",sumRootToLeaf(&t1));
	return 0;
}
