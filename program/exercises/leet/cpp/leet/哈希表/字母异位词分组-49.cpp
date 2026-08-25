//
// Created by 田庆新 on 2026/8/25.
//
/**
* 49. 字母异位词分组
中等
相关标签
premium lock icon
相关企业
给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。



示例 1:

输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]

输出: [["bat"],["nat","tan"],["ate","eat","tea"]]

解释：

在 strs 中没有字符串可以通过重新排列来形成 "bat"。
字符串 "nat" 和 "tan" 是字母异位词，因为它们可以重新排列以形成彼此。
字符串 "ate" ，"eat" 和 "tea" 是字母异位词，因为它们可以重新排列以形成彼此。
示例 2:

输入: strs = [""]

输出: [[""]]

示例 3:

输入: strs = ["a"]

输出: [["a"]]



提示：

1 <= strs.length <= 104
0 <= strs[i].length <= 100
strs[i] 仅包含小写字母
 * @return
 */
#include <algorithm>
#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <iostream>
using namespace std;

class Solution {
    uint64_t get_arr_hash(array<int, 26> &cnt_arr, uint64_t base = 131) {
        uint64_t ret = 0;
        for (int i = 0; i < 26; ++i)
            ret = ret * base + (i + 'a') * cnt_arr[i];
        return ret;
    }

public:
    vector<vector<string> > groupAnagrams(vector<string> &strs) {
        vector<vector<string> > ret;
        //不要存vector的迭代器，因为vector为动态数组，数组容量不够会进行扩容
        //扩容后数组地址已经变了，但是map中的value没有变化，会成为野指针
        unordered_map<uint64_t, int> cache;
        array<int, 26> buckets;
        int index = 0;
        for (string &str: strs) {
            buckets.fill(0);
            //统计词频
            for (char ch: str)
                buckets[ch - 'a']++;
            //计算哈希
            uint64_t hash_val = get_arr_hash(buckets);
            //如果哈希表中存在该key，获取这个entry
            unordered_map<uint64_t, int>::iterator cur_vec;
            if ((cur_vec = cache.find(hash_val)) == cache.end()) {
                ret.emplace(ret.end(), vector{str});
                cache.try_emplace(hash_val, index++);
            } else {
                ret[cur_vec->second].push_back(str);
            }
        }
        return ret;
    }
};

// int main() {
//     vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};
//     Solution sl;
//     const auto &vectors = sl.groupAnagrams(strs);
//     std::for_each(vectors.begin(), vectors.end(), [](const vector<string> &vc) {
//         std::for_each(vc.begin(), vc.end(), [](const string &str) { cout << str << " "; });
//         cout << endl;
//     });
//     return 0;
// }
