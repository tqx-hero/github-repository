//
// Created by Administrator on 2026/7/7.
//

/**
* 2058. 找出临界点之间的最小和最大距离
中等
相关标签
premium lock icon
相关企业
提示
链表中的 临界点 定义为一个 局部极大值点 或 局部极小值点 。

如果当前节点的值 严格大于 前一个节点和后一个节点，那么这个节点就是一个  局部极大值点 。

如果当前节点的值 严格小于 前一个节点和后一个节点，那么这个节点就是一个  局部极小值点 。

注意：节点只有在同时存在前一个节点和后一个节点的情况下，才能成为一个 局部极大值点 / 极小值点 。

给你一个链表 head ，返回一个长度为 2 的数组 [minDistance, maxDistance] ，其中 minDistance 是任意两个不同临界点之间的最小距离，maxDistance 是任意两个不同临界点之间的最大距离。如果临界点少于两个，则返回 [-1，-1] 。



示例 1：



输入：head = [3,1]
输出：[-1,-1]
解释：链表 [3,1] 中不存在临界点。
示例 2：



输入：head = [5,3,1,2,5,1,2]
输出：[1,3]
解释：存在三个临界点：
- [5,3,1,2,5,1,2]：第三个节点是一个局部极小值点，因为 1 比 3 和 2 小。
- [5,3,1,2,5,1,2]：第五个节点是一个局部极大值点，因为 5 比 2 和 1 大。
- [5,3,1,2,5,1,2]：第六个节点是一个局部极小值点，因为 1 比 5 和 2 小。
第五个节点和第六个节点之间距离最小。minDistance = 6 - 5 = 1 。
第三个节点和第六个节点之间距离最大。maxDistance = 6 - 3 = 3 。
示例 3：



输入：head = [1,3,2,2,3,2,2,2,7]
输出：[3,3]
解释：存在两个临界点：
- [1,3,2,2,3,2,2,2,7]：第二个节点是一个局部极大值点，因为 3 比 1 和 2 大。
- [1,3,2,2,3,2,2,2,7]：第五个节点是一个局部极大值点，因为 3 比 2 和 2 大。
最小和最大距离都存在于第二个节点和第五个节点之间。
因此，minDistance 和 maxDistance 是 5 - 2 = 3 。
注意，最后一个节点不算一个局部极大值点，因为它之后就没有节点了。
示例 4：



输入：head = [2,3,3,2]
输出：[-1,-1]
解释：链表 [2,3,3,2] 中不存在临界点。


提示：

链表中节点的数量在范围 [2, 105] 内
1 <= Node.val <= 105
 * @return
 */
#include <vector>
#include <iostream>
#include "../link/ListNode.h"
using namespace std;

inline int getMin(int x, int y) {
    return x <= y ? x : y;
}

class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode *head) {
        vector<int> ret;
        //只有2个节点，直接返回-1
        if (!head->next->next) {
            ret = {-1, -1};
            return ret;
        }
        //设置三个指针，prev、cur、next分别指向前一个节点、当前节点以及next节点
        ListNode *cur = head->next, *next = cur->next;
        int idx = 2, prevVal = head->val, curVal = cur->val, nextVal;
        int begin = -1, prevIdx = -1, min = INT_MAX;
        while (next) {
            nextVal = next->val;
            if ((curVal > prevVal && curVal > nextVal) || (curVal < prevVal && curVal < nextVal)) {
                //满足条件，记录当前idx
                if (prevIdx != -1) {
                    //计算两个index之间的距离，更新min
                    min = getMin(min, idx - prevIdx);
                } else
                //还未记录时，开始设置第一个满足条件的节点idx
                    begin = idx;
                prevIdx = idx;
            }
            cur = cur->next;
            next = next->next;
            prevVal = curVal;
            curVal = nextVal;
            idx++;
        }
        if (begin == prevIdx)
            ret = {-1, -1};
        else
            ret = {min, prevIdx - begin};
        return ret;
    }
};

// int main() {
//     //head = [5,3,1,2,5,1,2]
//     // ListNode l7{2};
//     // ListNode l6{1, &l7};
//     // ListNode l5{5, &l6};
//     // ListNode l4{2, &l5};
//     // ListNode l3{1, &l4};
//     // ListNode l2{3, &l3};
//     // ListNode l1{5, &l2};
//
//     //head = [1,3,2,2,3,2,2,2,7]
//     // ListNode l9{7};
//     // ListNode l8{2, &l9};
//     // ListNode l7{2, &l8};
//     // ListNode l6{2, &l7};
//     // ListNode l5{3, &l6};
//     // ListNode l4{2, &l5};
//     // ListNode l3{2, &l4};
//     // ListNode l2{3, &l3};
//     // ListNode l1{1, &l2};
//
//     //head = [2,2,1,3]
//     ListNode l4{3};
//     ListNode l3{1, &l4};
//     ListNode l2{2, &l3};
//     ListNode l1{2, &l2};
//
//     // //head = [2,3,3,2]
//     // ListNode l4{2};
//     // ListNode l3{3, &l4};
//     // ListNode l2{3, &l3};
//     // ListNode l1{2, &l2};
//
//     Solution solution;
//     vector<int> vs = solution.nodesBetweenCriticalPoints(&l1);
//     for (auto &num: vs) {
//         cout << num << endl;
//     }
//     return 0;
// }
