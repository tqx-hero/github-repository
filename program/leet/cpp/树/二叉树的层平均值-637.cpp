/**
 *637. 二叉树的层平均值
简单
相关标签
premium lock icon
相关企业
给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。

 

示例 1：



输入：root = [3,9,20,null,null,15,7]
输出：[3.00000,14.50000,11.00000]
解释：第 0 层的平均值为 3,第 1 层的平均值为 14.5,第 2 层的平均值为 11 。
因此返回 [3, 14.5, 11] 。
示例 2:



输入：root = [3,9,20,15,7]
输出：[3.00000,14.50000,11.00000]
 

提示：

树中节点数量在 [1, 104] 范围内
-231 <= Node.val <= 231 - 1
 */
#include <iostream>
#include <vector>
#include <queue>
#include "../tree/TreeNode.h"
using namespace std;

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
	    vector<double> ret;
	    queue<TreeNode*> mqueue;
	    mqueue.push(root);
	    while(!mqueue.empty()){
		    size_t mqsz = mqueue.size(),i = 0;
		    double sum =0;
		    while(i++ < mqsz){
			    TreeNode* cur =  mqueue.front();
			    sum += cur->val;
			    //将节点左右子树放入队列
			    if(cur->left)
				    mqueue.push(cur->left);
			    if(cur->right)
				    mqueue.push(cur->right);
			    mqueue.pop();
		    }
		    //计算平均值
		    ret.push_back(sum / mqsz);
	    }
	    return ret;
    }
};

int main(){
	TreeNode n7{7,nullptr,nullptr};
	TreeNode n15{15,nullptr,nullptr};
	TreeNode n20{20,&n15,&n7};
	TreeNode n9{9,nullptr,nullptr};
	TreeNode n3{3,&n9,&n20};
	Solution sl;
	const auto &vc = sl.averageOfLevels(&n3);
	for(int i=0;i<vc.size();++i)
		cout << vc[i] << " ";
	cout << endl;
	return 0;
}
