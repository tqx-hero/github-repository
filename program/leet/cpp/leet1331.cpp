//
// Created by Administrator on 2026/7/12.
//
/**
* 1331. 数组序号转换
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 arr ，请你将数组中的每个元素替换为它们排序后的序号。

序号代表了一个元素有多大。序号编号的规则如下：

序号从 1 开始编号。
一个元素越大，那么序号越大。如果两个元素相等，那么它们的序号相同。
每个数字的序号都应该尽可能地小。


示例 1：

输入：arr = [40,10,20,30]
输出：[4,1,2,3]
解释：40 是最大的元素。 10 是最小的元素。 20 是第二小的数字。 30 是第三小的数字。
示例 2：

输入：arr = [100,100,100]
输出：[1,1,1]
解释：所有元素有相同的序号。
示例 3：

输入：arr = [37,12,28,9,100,56,80,5,12]
输出：[5,3,4,2,8,6,7,1,3]


提示：

0 <= arr.length <= 105
-109 <= arr[i] <= 109
 * @return
 */
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
public:
    vector<int> arrayRankTransform(vector<int> &arr) {
        vector<int> result;
        if (arr.empty())
            return result;
        int size = arr.size();
        vector<int> sorted(arr);
        unordered_map<int, int> hashMap;
        hashMap.rehash(size);
        sort(sorted.begin(), sorted.end());
        int index = 1, i = 0;
        for (; i < size; i++) {
            //如果哈希表中不存在该值，设置该值的<key,value> = <arr[i],index>
            int num;
            if (!hashMap.count(num = sorted.at(i)))
                hashMap.emplace(num, index++);
        }
        //统计原数组，填入哈希表的value
        for (int nu: arr)
            result.push_back(hashMap.find(nu)->second);
        return result;
    }
};

// int main() {
//     vector<int> arr{37,12,28,9,100,56,80,5,12};
//     // vector<int> arr{40,10,20,30};
//     // vector<int> arr{100, 100, 100};
//     Solution sl;
//     vector<int> result = sl.arrayRankTransform(arr);
//     for (int i: result) {
//         cout << i << endl;
//     }
//     return 0;
// }
