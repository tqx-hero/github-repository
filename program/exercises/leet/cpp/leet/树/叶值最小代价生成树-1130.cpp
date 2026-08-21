//
// Created by Administrator on 2026/8/21.
//
/**
* 1130. 叶值的最小代价生成树
中等
相关标签
premium lock icon
相关企业
提示
给你一个正整数数组 arr，考虑所有满足以下条件的二叉树：

每个节点都有 0 个或是 2 个子节点。
数组 arr 中的值与树的中序遍历中每个叶节点的值一一对应。
每个非叶节点的值等于其左子树和右子树中叶节点的最大值的乘积。
在所有这样的二叉树中，返回每个非叶节点的值的最小可能总和。这个和的值是一个 32 位整数。

如果一个节点有 0 个子节点，那么该节点为叶节点。



示例 1：


输入：arr = [6,2,4]
输出：32
解释：有两种可能的树，第一种的非叶节点的总和为 36 ，第二种非叶节点的总和为 32 。
示例 2：


输入：arr = [4,11]
输出：44


提示：

2 <= arr.length <= 40
1 <= arr[i] <= 15
答案保证是一个 32 位带符号整数，即小于 231 。
 * @return
 */
#include <iostream>
#include <vector>
#include <list>
using namespace std;

class Solution {
    void calculate_sum(list<int> &list_cache, int &ret) {
        if (list_cache.size() == 1)
            return;
        list<int>::iterator begin_iter = list_cache.begin(), end_iter = list_cache.end(), prev_iter = begin_iter,
                max_iter;
        int max_mul = INT_MAX;
        for (++begin_iter; begin_iter != end_iter; ++begin_iter, ++prev_iter) {
            int cur_mul = *prev_iter * *begin_iter;
            if (cur_mul < max_mul) {
                max_mul = cur_mul;
                max_iter = begin_iter;
            }
        }
        //根据最大值的迭代器找到所在的节点，与前面的节点合并
        list<int>::iterator cur_iter = max_iter;
        int cur_val = *max_iter, prev_val = *--max_iter;
        *cur_iter = max(cur_val, prev_val);
        ret += max_mul;
        //删除前一个迭代器
        list_cache.erase(max_iter);
        calculate_sum(list_cache, ret);
    }

public:
    int mctFromLeafValues(vector<int> &arr) {
        //用双向链表存储当前节点中的最大值
        list<int> list_cache{arr.begin(), arr.end()};
        int ret = 0;
        calculate_sum(list_cache, ret);
        return ret;
    }
};

// int main() {
//     Solution sl;
//     vector<int> arr{6, 2, 4};
//     cout << sl.mctFromLeafValues(arr) << endl;
//     return 0;
// }
