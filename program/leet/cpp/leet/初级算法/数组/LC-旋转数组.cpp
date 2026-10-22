//
// Created by Administrator on 2026/8/9.
//
/**
* 旋转数组
给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。

  

示例 1:

输入: nums = [1,2,3,4,5,6,7], k = 3
输出: [5,6,7,1,2,3,4]
解释:
向右轮转 1 步: [7,1,2,3,4,5,6]
向右轮转 2 步: [6,7,1,2,3,4,5]
向右轮转 3 步: [5,6,7,1,2,3,4]
示例 2:

输入：nums = [-1,-100,3,99], k = 2
输出：[3,99,-1,-100]
解释:
向右轮转 1 步: [99,-1,-100,3]
向右轮转 2 步: [3,99,-1,-100]
  

提示：

1 <= nums.length <= 105
-231 <= nums[i] <= 231 - 1
0 <= k <= 105
  

进阶：

尽可能想出更多的解决方案，至少有 三种 不同的方法可以解决这个问题。
你可以使用空间复杂度为 O(1) 的 原地 算法解决这个问题吗？



作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/x2skh7/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;

//方法1：用双端队列模拟:时间复杂度O(k%n),空间复杂度O(n)
// class Solution {
// public:
//     void rotate(vector<int> &nums, int k) {
//         deque<int> nDeque{nums.begin(), nums.end()};
//         int size = static_cast<int>(nums.size()), cnt = k % size, i;
//         for (i = 0; i < cnt; i++) {
//             nDeque.push_front(nDeque.back());
//             nDeque.pop_back();
//         }
//         i = 0;
//         std::for_each(nDeque.begin(), nDeque.end(), [&nums,&i](const int x) {
//             nums[i++] = x;
//         });
//     }
// };
//翻转数组，然后以前(k%n)为分界线，前这些项再反转，后面那些翻转回来
//时间复杂度同样是O(n),空间复杂度O(1)
//没有使用额外空间
class Solution {
    void reverseArray(vector<int> &nums, int start, int end) {
        for (; start < end; start++, end--) {
            int tmp = nums[start];
            nums[start] = nums[end];
            nums[end] = tmp;
        }
    }

public:
    void rotate(vector<int> &nums, int k) {
        int size = static_cast<int>(nums.size()), cnt = k % size;
        if (!cnt || size == 1)
            return;
        reverseArray(nums, 0, size - 1);
        reverseArray(nums, 0, cnt - 1);
        reverseArray(nums, cnt, size - 1);
    }
};

// int main() {
//     vector<int> nums{-1, -100, 3, 99};
//     int k = 2;
//     // vector<int> nums{1, 2, 3, 4, 5, 6, 7};
//     // int k = 3;
//     Solution sl;
//     sl.rotate(nums, k);
//     std::for_each(nums.begin(), nums.end(), [](const int x) { cout << x << endl; });
//     return 0;
// }
