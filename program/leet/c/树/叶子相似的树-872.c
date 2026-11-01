/**
  872. 叶子相似的树
简单
相关标签
premium lock icon
相关企业
请考虑一棵二叉树上所有的叶子，这些叶子的值按从左到右的顺序排列形成一个 叶值序列 。



举个例子，如上图所示，给定一棵叶值序列为 (6, 7, 4, 9, 8) 的树。

如果有两棵二叉树的叶值序列是相同，那么我们就认为它们是 叶相似 的。

如果给定的两个根结点分别为 root1 和 root2 的树是叶相似的，则返回 true；否则返回 false 。



示例 1：



输入：root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
输出：true
示例 2：



输入：root1 = [1,2,3], root2 = [1,3,2]
输出：false


提示：

给定的两棵树结点数在 [1, 200] 范围内
给定的两棵树上的值在 [0, 200] 范围内
  */
#include "../tree/treenode.h"
#include <stdio.h>
typedef struct TreeNode TreeNode;

void summary_leaf(const TreeNode* root,int *hash_map,int *map_size){
	if(!root)
		return;
	summary_leaf(root->left,hash_map,map_size);
	if(!root->left && !root->right)
		hash_map[(*map_size)++] = root->val;
	summary_leaf(root->right,hash_map,map_size);
}

void match(const TreeNode* root,const int *hash_map,const int map_size,int *cur_idx,int *flag){
	if(!root || *flag == 0)
		return;
	match(root->left,hash_map,map_size,cur_idx,flag);
	if(!root->left && !root->right){
		if(*cur_idx >= map_size || hash_map[*cur_idx] != root->val){
			*flag = 0;
			return;
		}
		(*cur_idx)++;
	}
	match(root->right,hash_map,map_size,cur_idx,flag);
}

bool leafSimilar(struct TreeNode* root1, struct TreeNode* root2) {
	//把一棵树的叶子节点按照中序遍历依次放入一个数组，然后再遍历另一棵树依次比对
	int hash_map[200],map_size = 0;
	summary_leaf(root1,hash_map,&map_size);
	int cur_idx = 0,flag = 1;
	match(root2,hash_map,map_size,&cur_idx,&flag);
	return cur_idx == map_size && flag;
}

int main(){
	//root1 = [3,5,1,6,2,9,8,null,null,7,4], root2 = [3,5,1,6,7,4,2,null,null,null,null,null,null,9,8]
	/*
	TreeNode t4 = {4,NULL,NULL};
	TreeNode t7 = {7,NULL,NULL};
	TreeNode t6 = {6,NULL,NULL};
	TreeNode t8 = {8,NULL,NULL};
	TreeNode t9 = {9,NULL,NULL};
	TreeNode t2 = {2,&t7,&t4};
	TreeNode t1 = {1,&t9,&t8};
	TreeNode t5 = {5,&t6,&t2};
	TreeNode t3 = {3,&t5,&t1};

	TreeNode r6 = {6,NULL,NULL};
	TreeNode r7 = {7,NULL,NULL};
	TreeNode r4 = {4,NULL,NULL};
	TreeNode r9 = {9,NULL,NULL};
	TreeNode r8 = {8,NULL,NULL};
	TreeNode r5 = {5,&r6,&r7};
	TreeNode r2 = {2,&r9,&r8};
	TreeNode r1 = {1,&r4,&r2};
	TreeNode r3 = {3,&r5,&r1};
	*/

	TreeNode t4 = {4,NULL,NULL};
	TreeNode t7 = {7,NULL,NULL};
	TreeNode t6 = {6,NULL,NULL};
	TreeNode t8 = {8,NULL,NULL};
	TreeNode t9 = {9,NULL,NULL};
	TreeNode t10 = {10,NULL,NULL};
	TreeNode t11 = {11,&t8,&t10};
	TreeNode t2 = {2,&t9,&t11};
	TreeNode t1 = {1,&t4,&t2};
	TreeNode t5 = {5,&t6,&t7};
	TreeNode t3 = {3,&t5,&t1};

	TreeNode r6 = {6,NULL,NULL};
	TreeNode r7 = {7,NULL,NULL};
	TreeNode r4 = {4,NULL,NULL};
	TreeNode r9 = {9,NULL,NULL};
	TreeNode r8 = {8,NULL,NULL};
	TreeNode r2 = {2,&r7,&r4};
	TreeNode r5 = {5,&r6,&r2};
	TreeNode r1 = {1,&r9,&r8};
	TreeNode r3 = {3,&r5,&r1};

	printf("%d\n",leafSimilar(&t3,&r3));
	return 0;
}
