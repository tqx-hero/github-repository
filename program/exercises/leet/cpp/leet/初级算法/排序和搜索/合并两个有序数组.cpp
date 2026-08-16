//
// Created by Administrator on 2026/8/13.
//
/**
* 合并两个有序数组
给你两个按 非递减顺序 排列的整数数组 nums1 和 nums2，另有两个整数 m 和 n ，分别表示 nums1 和 nums2 中的元素数目。

请你 合并 nums2 到 nums1 中，使合并后的数组同样按 非递减顺序 排列。

注意：最终，合并后数组不应由函数返回，而是存储在数组 nums1 中。为了应对这种情况，nums1 的初始长度为 m + n，其中前 m 个元素表示应合并的元素，后 n 个元素为 0 ，应忽略。nums2 的长度为 n 。

  

示例 1：

输入：nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
输出：[1,2,2,3,5,6]
解释：需要合并 [1,2,3] 和 [2,5,6] 。
合并结果是 [1,2,2,3,5,6] ，其中斜体加粗标注的为 nums1 中的元素。
示例 2：

输入：nums1 = [1], m = 1, nums2 = [], n = 0
输出：[1]
解释：需要合并 [1] 和 [] 。
合并结果是 [1] 。
示例 3：

输入：nums1 = [0], m = 0, nums2 = [1], n = 1
输出：[1]
解释：需要合并的数组是 [] 和 [1] 。
合并结果是 [1] 。
注意，因为 m = 0 ，所以 nums1 中没有元素。nums1 中仅存的 0 仅仅是为了确保合并结果可以顺利存放到 nums1 中。
  

提示：

nums1.length == m + n
nums2.length == n
0 <= m, n <= 200
1 <= m + n <= 200
-109 <= nums1[i], nums2[j] <= 109

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnumcr/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    //从前往后排
    // void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
    //     std::copy_n(nums1.begin(), m, nums1.begin() + n);
    //     int n1_begin = n, n2_begin = 0, ret_index = 0, total_size = m + n;
    //     for (; n1_begin < total_size && n2_begin < n; ret_index++) {
    //         if (nums1[n1_begin] <= nums2[n2_begin])
    //             nums1[ret_index] = nums1[n1_begin++];
    //         else
    //             nums1[ret_index] = nums2[n2_begin++];
    //     }
    //     if (n2_begin < n)
    //         std::copy_n(nums2.begin() + n2_begin, n - n2_begin, nums1.begin() + ret_index);
    // }
    //从后往前排
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n) {
        vector<int>::reverse_iterator cur_iterator = nums1.rbegin(), n1_iterator = cur_iterator + n,
                n2_iterator = nums2.rbegin(),
                n1_end = nums1.rend(), n2_end = nums2.rend();
        while (n1_iterator != n1_end && n2_iterator != n2_end) {
            if (*n1_iterator > *n2_iterator)
                *(cur_iterator++) = *(n1_iterator++);
            else
                *(cur_iterator++) = *(n2_iterator++);
        }
        if (n2_iterator != n2_end)
            std::copy_n(n2_iterator, n2_end - n2_iterator, cur_iterator);
    }
};

// int main() {
//     vector<int> nums1 = {1, 2, 3, 0, 0, 0}, nums2 = {2, 5, 6};
//     int m = 3, n = 3;
//     Solution sl;
//     sl.merge(nums1, m, nums2, n);
//     std::for_each(nums1.begin(), nums1.end(), [](const int x) { cout << x << " "; });
//     cout << endl;
//     return 0;
// }
