#include <stdio.h>
#include <stdlib.h>

 struct Node {
      int val;
      int numChildren;
      struct Node** children;
 };

int dfs(struct Node* root){
	//没有孩子节点就返回1
	if(!root->numChildren)
		return 1;
	int max_cnt =0,i;
	for(i=0;i<root->numChildren;++i){
		int cur_cnt =  dfs(root->children[i]);
		max_cnt = cur_cnt > max_cnt ? cur_cnt : max_cnt;
	}
	return max_cnt + 1;
}

int maxDepth(struct Node* root) {
	if(!root)
		return 0;
	return dfs(root);
}
typedef struct Node Node;
int main(){
	Node node6={6,0,NULL};
	Node node5={5,0,NULL};
	Node node4={4,0,NULL};
	Node* n1[] = {&node5,&node6};
	Node node3={3,2,n1};
	Node node2={2,0,NULL};
	Node* n2[] = {&node3,&node2,&node4};
	Node node1={1,3,n2};
	printf("%d\n",maxDepth(&node1));
	return 0;
}
