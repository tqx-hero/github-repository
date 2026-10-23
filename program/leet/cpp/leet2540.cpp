//
// Created by Administrator on 2026/7/13.
//
/**
* 2540. 最小公共值
简单
相关标签
premium lock icon
相关企业
提示
给你两个整数数组 nums1 和 nums2 ，它们已经按非降序排序，请你返回两个数组的 最小公共整数 。如果两个数组 nums1 和 nums2 没有公共整数，请你返回 -1 。

如果一个整数在两个数组中都 至少出现一次 ，那么这个整数是数组 nums1 和 nums2 公共 的。



示例 1：

输入：nums1 = [1,2,3], nums2 = [2,4]
输出：2
解释：两个数组的最小公共元素是 2 ，所以我们返回 2 。
示例 2：

输入：nums1 = [1,2,3,6], nums2 = [2,3,4,5]
输出：2
解释：两个数组中的公共元素是 2 和 3 ，2 是较小值，所以返回 2 。


提示：

1 <= nums1.length, nums2.length <= 105
1 <= nums1[i], nums2[j] <= 109
nums1 和 nums2 都是 非降序 的。
 * @return
 */
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int getCommon(vector<int> &nums1, vector<int> &nums2) {
        unordered_set<int> hashSet;
        int n1Len = nums1.size(), n2Len = nums2.size(), n2Min = nums2.at(0), n2Max = nums2.at(n2Len - 1), i = 0;
        for (; i < n1Len; i++) {
            int cur;
            if ((cur = nums1.at(i)) < n2Min)
                continue;
            if (cur == n2Min)
                return n2Min;
            if (cur > n2Max)
                break;
            hashSet.emplace(cur);
        }
        if (hashSet.empty())
            return -1;
        for (i = 0; i < n2Len; i++) {
            int num = nums2.at(i);
            if (hashSet.count(num))
                return num;
        }
        return -1;
    }
};

// int main() {
//     return 0;
// }
