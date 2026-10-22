//
// Created by 田庆新 on 2026/9/5.
//
/**
* 102. 二叉树的层序遍历
已解答
中等
相关标签
premium lock icon
相关企业
提示
给你二叉树的根节点 root ，返回其节点值的 层序遍历 。 （即逐层地，从左到右访问所有节点）。



示例 1：


输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
示例 2：

输入：root = [1]
输出：[[1]]
示例 3：

输入：root = []
输出：[]


提示：

树中节点数目在范围 [0, 2000] 内
-1000 <= Node.val <= 1000
 * @return
 */
#include "../../link/TreeNode.h"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > ret;
        if (!root)
            return ret;
        queue<TreeNode *> cache;
        cache.push(root);
        int cnt, i;
        while ((cnt = static_cast<int>(cache.size())) != 0) {
            vector<int> vc(cnt);
            i = 0;
            while (i < cnt) {
                TreeNode *front = cache.front();
                vc[i] = front->val;
                //子节点入队列
                if (front->left)
                    cache.push(front->left);
                if (front->right)
                    cache.push(front->right);
                //弹出对头节点，增加计数
                cache.pop();
                i++;
            }
            //当前层添加完成，放入总的统计数组
            ret.push_back(vc);
        }
        return ret;
    }
};

// int main() {
//     return 0;
// }
