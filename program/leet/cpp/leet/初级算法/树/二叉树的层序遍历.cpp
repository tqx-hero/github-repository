//
// Created by Administrator on 2026/8/13.
//
/**
* 二叉树的层序遍历
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

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnldjj/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <queue>
#include <vector>
#include "../../../link/TreeNode.h"
using namespace std;

class Solution {
public:
    vector<vector<int> > levelOrder(TreeNode *root) {
        vector<vector<int> > result;
        if (!root)
            return result;
        queue<TreeNode *> cache;
        cache.push(root);
        while (!cache.empty()) {
            size_t q_size = cache.size();
            vector<int> vc;
            vc.reserve(q_size);
            for (int i = 0; i < q_size; i++) {
                //对每一个节点取出，放入结果集，并且把它的不为空的左右子树放入队列
                auto &tree_node = cache.front();
                vc.push_back(tree_node->val);
                if (tree_node->left)
                    cache.push(tree_node->left);
                if (tree_node->right)
                    cache.push(tree_node->right);
                cache.pop();
            }
            result.push_back(vc);
        }
        return result;
    }
};

// int main() {
//     return 0;
// }
