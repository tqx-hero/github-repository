//
// Created by Administrator on 2026/7/25.
//
/**
* 3507. 移除最小数对使数组有序 I
简单
相关标签
premium lock icon
相关企业
提示
给你一个数组 nums，你可以执行以下操作任意次数：

选择 相邻 元素对中 和最小 的一对。如果存在多个这样的对，选择最左边的一个。
用它们的和替换这对元素。
返回将数组变为 非递减 所需的 最小操作次数 。

如果一个数组中每个元素都大于或等于它前一个元素（如果存在的话），则称该数组为非递减。



示例 1：

输入： nums = [5,2,3,1]

输出： 2

解释：

元素对 (3,1) 的和最小，为 4。替换后 nums = [5,2,4]。
元素对 (2,4) 的和为 6。替换后 nums = [5,6]。
数组 nums 在两次操作后变为非递减。

示例 2：

输入： nums = [1,2,2]

输出： 0

解释：

数组 nums 已经是非递减的。



提示：

1 <= nums.length <= 50
-1000 <= nums[i] <= 1000
 * @return
 */
#include <iostream>
#include <list>
#include <vector>
using namespace std;

class Solution {
public:
    int minimumPairRemoval(vector<int> &nums) {
        int i, j, cnt = 0;
        bool ordered = true;
        if (nums.size() == 1)
            return 0;
        const int max_sum = INT_MAX;
        list<int> numList(nums.begin(), nums.end());
        do {
            list<int>::iterator minIter, begin, last;
            int minNum = max_sum;
            for (begin = numList.begin(), last = --numList.end(); begin != last;) {
                int ni = *begin, nj = *++begin;
                if (ordered)
                    ordered = nj >= ni;
                int num = ni + nj;
                if (num < minNum) {
                    minIter = begin;
                    minNum = num;
                }
            }
            if (ordered)
                return cnt;
            //无序，将minIter迭代器中的值更新为minNum,删除前一个迭代器
            *minIter = minNum;
            minNum = max_sum;
            numList.erase(--minIter);
            ordered = true;
            cnt++;
        } while (true);
    }
};

// int main() {
//     vector<int> nums{564, 561, 543, 576, -379, 510, 54, 383, -615, 468, 431, 601, 412, -397, 421, 183, 160, 415};
//     // vector<int> nums{1,2,2};
//     // vector<int> nums{5, 2, 3, 1};
//     Solution sl;
//     cout << sl.minimumPairRemoval(nums) << endl;
//     return 0;
// }
