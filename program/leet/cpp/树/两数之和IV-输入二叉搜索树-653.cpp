/**
 *653. 两数之和 IV - 输入二叉搜索树
简单
相关标签
premium lock icon
相关企业
给定一个二叉搜索树 root 和一个目标结果 k，如果二叉搜索树中存在两个元素且它们的和等于给定的目标结果，则返回 true。

 

示例 1：


输入: root = [5,3,6,2,4,null,7], k = 9
输出: true
示例 2：


输入: root = [5,3,6,2,4,null,7], k = 28
输出: false
 

提示:

二叉树的节点个数的范围是  [1, 104].
-104 <= Node.val <= 104
题目数据保证，输入的 root 是一棵 有效 的二叉搜索树
-105 <= k <= 105
 */
#include "../tree/TreeNode.h"
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
	unordered_set<int> cache;
public:
    bool findTarget(TreeNode* root, int k) {
	    if(!root)
		    return false;
	    //缓存中存在，返回true
	    if(cache.count(k - root->val))
		    return true;
	    //将root加入cache
	    cache.emplace(root->val);
	    return findTarget(root->left,k) || findTarget(root->right,k);
    }
};

int main(){
	//root = [5,3,6,2,4,null,7], k = 9
	TreeNode n7{7,nullptr,nullptr};
	TreeNode n4{4,nullptr,nullptr};
	TreeNode n2{2,nullptr,nullptr};
	TreeNode n6{6,nullptr,&n7};
	TreeNode n3{3,&n2,&n4};
	TreeNode n5{5,&n3,&n6};
	Solution sl;
	cout << sl.findTarget(&n5,9) << endl;
	return 0;
}
