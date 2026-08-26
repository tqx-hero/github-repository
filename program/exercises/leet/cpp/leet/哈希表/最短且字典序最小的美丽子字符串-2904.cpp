//
// Created by 田庆新 on 2026/8/26.
//
/**
* 2904. 最短且字典序最小的美丽子字符串
中等
相关标签
premium lock icon
相关企业
提示
给你一个二进制字符串 s 和一个正整数 k 。

如果 s 的某个子字符串中 1 的个数恰好等于 k ，则称这个子字符串是一个 美丽子字符串 。

令 len 等于 最短 美丽子字符串的长度。

返回长度等于 len 且字典序 最小 的美丽子字符串。如果 s 中不含美丽子字符串，则返回一个 空 字符串。

对于相同长度的两个字符串 a 和 b ，如果在 a 和 b 出现不同的第一个位置上，a 中该位置上的字符严格大于 b 中的对应字符，则认为字符串 a 字典序 大于 字符串 b 。

例如，"abcd" 的字典序大于 "abcc" ，因为两个字符串出现不同的第一个位置对应第四个字符，而 d 大于 c 。


示例 1：

输入：s = "100011001", k = 3
输出："11001"
解释：示例中共有 7 个美丽子字符串：
1. 子字符串 "100011001" 。
2. 子字符串 "100011001" 。
3. 子字符串 "100011001" 。
4. 子字符串 "100011001" 。
5. 子字符串 "100011001" 。
6. 子字符串 "100011001" 。
7. 子字符串 "100011001" 。
最短美丽子字符串的长度是 5 。
长度为 5 且字典序最小的美丽子字符串是子字符串 "11001" 。
示例 2：

输入：s = "1011", k = 2
输出："11"
解释：示例中共有 3 个美丽子字符串：
1. 子字符串 "1011" 。
2. 子字符串 "1011" 。
3. 子字符串 "1011" 。
最短美丽子字符串的长度是 2 。
长度为 2 且字典序最小的美丽子字符串是子字符串 "11" 。
示例 3：

输入：s = "000", k = 1
输出：""
解释：示例中不存在美丽子字符串。


提示：

1 <= s.length <= 100
1 <= k <= s.length
 * @return
 */
#include <cstdint>
#include <string>
#include <iostream>
#include <set>
#include <array>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
    struct pair_node {
        int begin_index;
        uint64_t first, second;

        pair_node(int begin_index, uint64_t first, uint64_t second = 0)
            : begin_index(begin_index),
              first(first),
              second(second) {
        }
    };

    struct compared_node {
        auto operator()(const pair_node &t1, const pair_node &t2) const -> decltype(1 == 2) {
            //再比较这两个无符号long long类型值
            if (t1.first != t2.first)
                return t1.first < t2.first;
            return t1.second < t2.second;
        }
    };

    int get_min_ordered_index(string &s, int len, vector<int> &index_list) {
        //使用红黑树进行排序
        set<pair_node, compared_node> tree_set;
        //是否只需要进行2次计算？
        bool twice = len > 64;
        int cal_len = min(len, 64);
        for (int begin_index: index_list) {
            //将各字符串计算它的无符号64位值(1个或者2个)
            uint64_t first_val = get_bound_value(s, begin_index, begin_index + cal_len - 1);
            uint64_t second_val = 0;
            //计算超过64位的那部分子串的value
            if (twice)
                second_val = get_bound_value(s, begin_index + 64, begin_index + len - 1);
            tree_set.emplace(begin_index, first_val, second_val);
        }
        return tree_set.begin()->begin_index;
    }

    uint64_t get_bound_value(string &str, int left, int right) {
        uint64_t ret = 0;
        int i = 0;
        for (; right >= left; --right, ++i)
            ret ^= (static_cast<uint64_t>(str[right] - '0') << i);
        return ret;
    }

public:
    string shortestBeautifulSubstring(string s, int k) {
        //缓存字符串的信息<字符串长度，该长度下的子串在原串的起始下标>
        unordered_map<int, vector<int> > cache;
        //统计当前最小长度，小于等于该长度的放入缓存
        int min_len = INT32_MAX, size = static_cast<int>(s.size());
        array<int, 2> buckets{0};
        //滑动窗口进行字符串统计
        int left = 0, right = left;
        for (; right < size;) {
            //当子串中的1的个数小于k，right++,当然前提条件必须是right不能越界
            while (right < size && buckets[1] < k)
                buckets[s[right++] - '0']++;
            //到这里如果1的个数还少于k，说明已经到头了，跳出循环开始统计
            if (buckets[1] < k)
                break;
            //没到头，即找到了一个美丽字符串。
            //因为需要找到最短子串，这里先不统计，直接left++缩小子串空间,直到1的个数小于k为止
            //再记录子串起始下标为left-1，长度为right-(left-1)+1
            while (buckets[1] == k)
                buckets[s[left++] - '0']--;
            //到这里刚刚满足[left-1,right-1]区间1个数等于k，且是以right-1为右边界len最短的。
            int cur_min_len = right - left + 1;
            //小于等于时直接追加即可,大于跳过
            if (cur_min_len <= min_len) {
                cache[cur_min_len].push_back(left - 1);
                //更新最小值
                min_len = cur_min_len;
            }
        }
        if (min_len == INT32_MAX)
            return "";
        //min_len的子串集合统计结束，接下来就是如何找出相同长度下的最小子串
        //方法是使用红黑树set，将每个集合中的子串按照64位拆分(无符号long long类型)
        //因为原字符串总长度不超过100，所以使用2个无符号long long值必定能表示所有子串
        int begin_index = get_min_ordered_index(s, min_len, cache[min_len]);
        return string{s.begin() + begin_index, s.begin() + begin_index + min_len};
    }
};

// int main() {
//     string s = "000";
//     // string s = "1011";
//     // string s = "100011001";
//     int k = 1;
//     // int k = 3;
//     Solution sl;
//     cout << sl.shortestBeautifulSubstring(s, k) << endl;
//     return 0;
// }
