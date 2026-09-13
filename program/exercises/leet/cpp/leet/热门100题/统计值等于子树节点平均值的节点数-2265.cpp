/**
 * 2265. 统计值等于子树平均值的节点数
中等
相关标签
premium lock icon
相关企业
提示
给你一棵二叉树的根节点 root ，找出并返回满足要求的节点数，要求节点的值等于其 子树 中值的 平均值 。

注意：

n 个元素的平均值可以由 n 个元素 求和 然后再除以 n ，并 向下舍入 到最近的整数。
root 的 子树 由 root 和它的所有后代组成。
 

示例 1：


输入：root = [4,8,5,0,1,null,6]
输出：5
解释：
对值为 4 的节点：子树的平均值 (4 + 8 + 5 + 0 + 1 + 6) / 6 = 24 / 6 = 4 。
对值为 5 的节点：子树的平均值 (5 + 6) / 2 = 11 / 2 = 5 。
对值为 0 的节点：子树的平均值 0 / 1 = 0 。
对值为 1 的节点：子树的平均值 1 / 1 = 1 。
对值为 6 的节点：子树的平均值 6 / 1 = 6 。
示例 2：


输入：root = [1]
输出：1
解释：对值为 1 的节点：子树的平均值 1 / 1 = 1。
 

提示：

树中节点数目在范围 [1, 1000] 内
0 <= Node.val <= 1000
 */
#include "../../link/TreeNode.h"
class Solution {
    int cnt=0;
    struct AveEntry{
        int node_count;
        int total_sum;

        AveEntry(int node_count = 0,int total_sum = 0) : node_count(node_count) , total_sum(total_sum) {
        }
    };

    void dfs(TreeNode* root,AveEntry& ave){
        if(!root)
            return;
        //统计分别左子树与右子树的平均值，在计算当前节点的平均值
        AveEntry av_left,av_right;
        dfs(root->left,av_left);
        dfs(root->right,av_right);
        ave.total_sum = root->val + av_left.total_sum + av_right.total_sum;
        ave.node_count = 1+av_left.node_count+av_right.node_count;
        if(ave.total_sum / ave.node_count == root->val)
            cnt++;
    }

public:
    int averageOfSubtree(TreeNode* root) {
        //从叶子节点开始自底向上递归计算
        AveEntry av;
        dfs(root,av);
        return cnt;
    }
};

// int main(){
//     return 0;
// }