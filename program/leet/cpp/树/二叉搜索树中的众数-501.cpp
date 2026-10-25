/**
 * 501. 二叉搜索树中的众数
简单
相关标签
premium lock icon
相关企业
给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有 众数（即，出现频率最高的元素）。

如果树中有不止一个众数，可以按 任意顺序 返回。

假定 BST 满足如下定义：

结点左子树中所含节点的值 小于等于 当前节点的值
结点右子树中所含节点的值 大于等于 当前节点的值
左子树和右子树都是二叉搜索树


示例 1：


输入：root = [1,null,2,2]
输出：[2]
示例 2：

输入：root = [0]
输出：[0]


提示：

树中节点的数目在范围 [1, 104] 内
-105 <= Node.val <= 105


进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）
 */
#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
#include "../tree/TreeNode.h"
using namespace std;
//TODO
class Solution
{
	int current_num,current_cnt;//当前值与当前值的出现次数
	vector<int> ret;//结果数组
	int ret_cnt;//结果数组的元素出现次数
	
	void dfs(TreeNode* root){
		if(!root)
			return;
		dfs(root->left);
		if(root->val == current_num){
			++current_cnt;
		}else{

		 	if (current_cnt == ret_cnt)//记录的值出现次数与数组记录的最多次数相同，直接添加
				ret.push_back(current_num);
			else if(current_cnt > ret_cnt){
				ret.clear();
				ret.push_back(current_num);
				ret_cnt = current_cnt;
			}
			current_num = root->val;
			current_cnt = 1;
		}
		dfs(root->right);
	}
public:
    vector<int> findMode(TreeNode *root)
    {
	ret_cnt = -1;
	current_cnt = 0;
	current_num = INT_MIN;
	dfs(root);
	if(current_cnt == ret_cnt)
		ret.push_back(current_num);
	else if(current_cnt > ret_cnt)
		return vector<int>{current_num};
	return ret;
    }
};

int main()
{
	TreeNode n3{2,nullptr,nullptr};
	TreeNode n2{2,&n3,nullptr};
	TreeNode n1{1,nullptr,&n2};
	Solution sl;
	const auto & vc = sl.findMode(&n1);
	for_each(vc.begin(),vc.end(),[](const int& num){cout << num << " ";});
	cout << endl;
    	return 0;
}
