/**
 * 257. 二叉树的所有路径
简单
相关标签
premium lock icon
相关企业
给你一个二叉树的根节点 root。

按 任意顺序 ，返回所有 从根节点到叶子节点 的路径。

叶子节点 是指没有子节点的节点。

 
示例 1：


输入：root = [1,2,3,null,5]
输出：["1->2->5","1->3"]
示例 2：

输入：root = [1]
输出：["1"]
 

提示：

树中节点的数目在范围 [1, 100] 内
-100 <= Node.val <= 100
 */
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "../../link/TreeNode.h"
using namespace std;
class Solution {
    vector<string> ret;
    
    void dfs(TreeNode* node,string str,bool addational){
        if(addational)
            str += "->";
        str += to_string(node->val);
        if(!node->left && !node->right){
            ret.push_back(str);
            return;
        }
        if(node->left)
            dfs(node->left,str,true);
        if(node->right)
            dfs(node->right,str,true);
    }

public:
    vector<string> binaryTreePaths(TreeNode* root) {
        string str;
        dfs(root,str,false);
        return ret;
    }
};

// int main(){
//     //root = [1,2,3,null,5]
//     TreeNode t5(5);
//     TreeNode t3(3);
//     TreeNode t2(2,nullptr,&t5);
//     TreeNode t1(1,&t2,&t3);
//     Solution sl;
//     const auto& vc = sl.binaryTreePaths(&t1);
//     for_each(vc.begin(),vc.end(),[](const string& str){cout << str << " ";});
//     cout << endl;
//     return 0;
// }