#include "../node/treenode.h"
#include <stdio.h>
#include <limits.h>

int min(int x,int y){
	return x < y ? x : y;
}

void dfs(struct TreeNode* root,int *before_ptr,int *min_ptr){
	if(!root)
		return;
	dfs(root->left,before_ptr,min_ptr);
	if(*before_ptr != -1)
		*min_ptr = min(*min_ptr,root->val - *before_ptr);
        *before_ptr = root->val;
	dfs(root->right,before_ptr,min_ptr);       
}

int getMinimumDifference(struct TreeNode* root) {
	int before_val = -1,min_val = INT_MAX;
	dfs(root,&before_val,&min_val);
	return min_val;
}

int main(){
	struct TreeNode node1 ={1,NULL,NULL};
	struct TreeNode node3 ={3,NULL,NULL};
	struct TreeNode node2 ={2,&node1,&node3};
	struct TreeNode node6 ={6,NULL,NULL};
	struct TreeNode node4 ={4,&node2,&node6};
	printf("%d\n",getMinimumDifference(&node4));
	return 0;
}
