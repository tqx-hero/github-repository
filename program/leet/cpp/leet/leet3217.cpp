//
// Created by Administrator on 2026/7/11.
//
/**
* 3217. 从链表中移除在数组中存在的节点
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 nums 和一个链表的头节点 head。从链表中移除所有存在于 nums 中的节点后，返回修改后的链表的头节点。



示例 1：

输入： nums = [1,2,3], head = [1,2,3,4,5]

输出： [4,5]

解释：



移除数值为 1, 2 和 3 的节点。

示例 2：

输入： nums = [1], head = [1,2,1,2,1,2]

输出： [2,2,2]

解释：



移除数值为 1 的节点。

示例 3：

输入： nums = [5], head = [1,2,3,4]

输出： [1,2,3,4]

解释：



链表中不存在值为 5 的节点。



提示：

1 <= nums.length <= 105
1 <= nums[i] <= 105
nums 中的所有元素都是唯一的。
链表中的节点数在 [1, 105] 的范围内。
1 <= Node.val <= 105
输入保证链表中至少有一个值没有在 nums 中出现过。
 * @return
 */
#include <unordered_set>

#include "../link/ListNode.h"
#include <vector>
using namespace std;

class Solution {
public:
    ListNode *modifiedList(vector<int> &nums, ListNode *head) {
        unordered_set<int> set;
        size_t size = nums.size();
        set.rehash(size);
        for (int i = 0; i < size; i++)
            set.emplace(nums[i]);
        ListNode sentinel(0, head), *cur = &sentinel, *next = nullptr;
        while ((next = cur->next)) {
            //哈希表中存在值，删除该节点
            if (set.count(next->val))
                cur->next = next->next;
                // delete next;
            else
                cur = cur->next;
        }
        return sentinel.next;
    }
};

// int main() {
//     return 0;
// }
