/**
 *572. 另一棵树的子树
简单
相关标签
premium lock icon
相关企业
提示
给你两棵二叉树 root 和 subRoot 。检验 root 中是否包含和 subRoot 具有相同结构和节点值的子树。如果存在，返回 true ；否则，返回 false 。

二叉树 tree 的一棵子树包括 tree 的某个节点和这个节点的所有后代节点。tree 也可以看做它自身的一棵子树。

 

示例 1：


输入：root = [3,4,5,1,2], subRoot = [4,1,2]
输出：true
示例 2：


输入：root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
输出：false
 

提示：

root 树上的节点数量范围是 [1, 2000]
subRoot 树上的节点数量范围是 [1, 1000]
-104 <= root.val <= 104
-104 <= subRoot.val <= 104
 */
#include <iostream>
#include "../tree/TreeNode.h"
using namespace std;

class Solution {
	TreeNode* subroot;
	bool helper(TreeNode* root,TreeNode* subRoot){
	    if(!root && !subRoot)
		    return true;
	    //任意一个为null另一个不为null，或者值不相等，返回false
	    if(!root || !subRoot)
		    return false;
	    bool flag = root->val == subRoot->val;
	    //如果值相等，就继续往下比较
	    if(flag)
		    flag =  helper(root->left,subRoot->left) && helper(root->right,subRoot->right);
	    if(flag)
		    return true;
	    //不相等就看是不是根节点，如果是根节点，root往下找
	    if(subroot == subRoot)
		    return helper(root->left,subRoot) || helper(root->right,subRoot);
	    else
		    return false;
	}
public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
	    subroot = subRoot;
	    return helper(root,subRoot);
    }
};

int main(){
	//root = [3,4,5,1,2], subRoot = [4,1,2]
	/*
	TreeNode n2{2,nullptr,nullptr};
	TreeNode n1{1,nullptr,nullptr};
	TreeNode n5{5,nullptr,nullptr};
	TreeNode n4{4,&n1,&n2};
	TreeNode n3{3,&n4,&n5};

	TreeNode m2{2,nullptr,nullptr};
	TreeNode m1{1,nullptr,nullptr};
	TreeNode m4{4,&m1,&m2};
	*/

	//root = [3,4,5,1,2,null,null,null,null,0], subRoot = [4,1,2]
	TreeNode n0{0,nullptr,nullptr};
	TreeNode n2{2,&n0,nullptr};
	TreeNode n1{1,nullptr,nullptr};
	TreeNode n5{5,nullptr,nullptr};
	TreeNode n4{4,&n1,&n2};
	TreeNode n3{3,&n4,&n5};

	TreeNode m2{2,nullptr,nullptr};
	TreeNode m1{1,nullptr,nullptr};
	TreeNode m4{4,&m1,&m2};
	Solution sl;
	cout << sl.isSubtree(&n3,&m4) << endl;
	return 0;
}
