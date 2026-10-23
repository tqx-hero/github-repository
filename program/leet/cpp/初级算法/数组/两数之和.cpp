//
// Created by Administrator on 2026/8/9.
//
/**
* 两数之和
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案，并且你不能使用两次相同的元素。

你可以按任意顺序返回答案。

  

示例 1：

输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：

输入：nums = [3,2,4], target = 6
输出：[1,2]
示例 3：

输入：nums = [3,3], target = 6
输出：[0,1]
  

提示：

2 <= nums.length <= 104
-109 <= nums[i] <= 109
-109 <= target <= 109
只会存在一个有效答案
  

进阶：你可以想出一个时间复杂度小于 O(n2) 的算法吗？

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/x2jrse/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int> &nums, int target) {
        unordered_map<int, int> cache;
        vector<int> ret;
        ret.reserve(2);
        int i = 0, size = static_cast<int>(nums.size());
        for (i = 0; i < size; i++) {
            int t = target - nums[i];
            if (cache.count(t))
                return vector<int>{i, cache[t]};
            cache[nums[i]] = i;
        }
        return ret;
    }
};

// int main() {
//     return 0;
// }
