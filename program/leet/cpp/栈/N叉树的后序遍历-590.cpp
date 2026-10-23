//
// Created by Administrator on 2026/8/6.
//
/**
*
代码
测试用例
测试用例
测试结果
590. N 叉树的后序遍历
简单
相关标签
premium lock icon
相关企业
给定一个 n 叉树的根节点 root ，返回 其节点值的 后序遍历 。

n 叉树 在输入中按层序遍历进行序列化表示，每组子节点由空值 null 分隔（请参见示例）。



示例 1：



输入：root = [1,null,3,2,4,null,5,6]
输出：[5,6,3,2,4,1]
示例 2：



输入：root = [1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：[2,6,14,11,7,3,12,8,4,13,9,10,5,1]


提示：

节点总数在范围 [0, 104] 内
0 <= Node.val <= 104
n 叉树的高度小于或等于 1000


进阶：递归法很简单，你可以使用迭代法完成此题吗?
 * @return
 */
#include <algorithm>
#include <stack>
#include <unordered_set>
#include <vector>
#include <iostream>
using namespace std;

class Node {
public:
    int val;
    vector<Node *> children;

    Node() {
    }

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

/**
 * 迭代法，用栈实现后序遍历
 */
class Solution {
public:
    vector<int> postorder(Node *root) {
        if (!root)
            return vector<int>{};
        vector<int> result;
        stack<Node *> nodeStack;
        unordered_set<Node *> cache;
        nodeStack.push(root);
        while (!nodeStack.empty()) {
            auto node = nodeStack.top();
            vector<Node *> &childs = node->children;
            if (childs.empty() || cache.count(node)) {
                //如果子节点为空，或者之前已经将子节点压入栈内，直接将数据放入result，弹栈
                result.push_back(node->val);
                nodeStack.pop();
            } else {
                //如果有子节点，并且还没有把子节点压入栈内，逆序压入子节点
                for (int i = static_cast<int>(childs.size()) - 1; i >= 0; i--)
                    nodeStack.push(childs[i]);
                cache.emplace(node);
            }
        }
        return result;
    }
};

// int main() {
//     Node n6(6);
//     Node n5(5);
//     Node n4(4);
//     Node n3(2);
//     Node n2(3, vector<Node *>{&n5, &n6});
//     Node n1(1, vector<Node *>{&n2, &n3, &n4});
//     Solution sl;
//     const auto & ret = sl.postorder(&n1);
//     std::for_each(ret.begin(),ret.end(),[](const int x){cout << x << endl;});
//     return 0;
// }
