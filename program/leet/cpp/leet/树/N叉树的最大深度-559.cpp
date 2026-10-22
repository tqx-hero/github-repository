/**
 *559. N 叉树的最大深度
简单
相关标签
premium lock icon
相关企业
给定一个 N 叉树，找到其最大深度。

最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。

N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔（请参见示例）。

 

示例 1：



输入：root = [1,null,3,2,4,null,5,6]
输出：3
示例 2：



输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：5
 

提示：

树的深度不会超过 1000 。
树的节点数目位于 [0, 104] 之间。
 */
#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

class Solution {

	int dfs(Node* root){
	        //没有孩子节点，返回1
        	if(root->children.size() == 0)
                	return 1;
		int max_cnt =0;
		//有孩子节点，就遍历孩子节点，直到叶子结点，自底向上加回来
		for(Node* node : root->children)
			max_cnt = std::max(dfs(node),max_cnt);
		return max_cnt + 1;
	}
public:
    int maxDepth(Node* root) {
	if(!root)
		return 0;
	return dfs(root);
    }
};

int main(){
	Node  node6{6,vector<Node*>{}};
	Node  node5{5,vector<Node*>{}};
	Node  node4{4,vector<Node*>{}};
	Node  node3{3,vector<Node*>{&node5,&node6}};
	Node  node2{2,vector<Node*>{}};
	Node  node1{1,vector<Node*>{&node3,&node2,&node4}};
	Solution sl;
	cout << sl.maxDepth(&node1) << endl;
	return 0;
}
