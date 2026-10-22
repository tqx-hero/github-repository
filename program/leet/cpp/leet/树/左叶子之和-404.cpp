/**
 * 404. 左叶子之和
简单
相关标签
premium lock icon
相关企业
给定二叉树的根节点 root ，返回所有左叶子之和。



示例 1：



输入: root = [3,9,20,null,null,15,7]
输出: 24
解释: 在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24
示例 2:

输入: root = [1]
输出: 0


提示:

节点数在 [1, 1000] 范围内
-1000 <= Node.val <= 1000

 */
#include "../../link/TreeNode.h"
using namespace std;
class Solution
{
    int sum = 0;
    void dfs(TreeNode *root, bool left)
    {
        if (!root)
            return;
        if (left && !root->left && !root->right)
        {
            sum += root->val;
            return;
        }
        dfs(root->left, true);
        dfs(root->right, false);
    }

public:
    int sumOfLeftLeaves(TreeNode *root)
    {
        dfs(root, false);
        return sum;
    }
};

// int main()
// {
//     return 0;
// }