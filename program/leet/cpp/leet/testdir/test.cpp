/**
 * 506. 相对名次
简单
相关标签
premium lock icon
相关企业
给你一个长度为 n 的整数数组 score ，其中 score[i] 是第 i 位运动员在比赛中的得分。所有得分都 互不相同 。

运动员将根据得分 决定名次 ，其中名次第 1 的运动员得分最高，名次第 2 的运动员得分第 2 高，依此类推。运动员的名次决定了他们的获奖情况：

名次第 1 的运动员获金牌 "Gold Medal" 。
名次第 2 的运动员获银牌 "Silver Medal" 。
名次第 3 的运动员获铜牌 "Bronze Medal" 。
从名次第 4 到第 n 的运动员，只能获得他们的名次编号（即，名次第 x 的运动员获得编号 "x"）。
使用长度为 n 的数组 answer 返回获奖，其中 answer[i] 是第 i 位运动员的获奖情况。



示例 1：

输入：score = [5,4,3,2,1]
输出：["Gold Medal","Silver Medal","Bronze Medal","4","5"]
解释：名次为 [1st, 2nd, 3rd, 4th, 5th] 。
示例 2：

输入：score = [10,3,8,9,4]
输出：["Gold Medal","5","Bronze Medal","Silver Medal","4"]
解释：名次为 [1st, 5th, 3rd, 2nd, 4th] 。


提示：

n == score.length
1 <= n <= 104
0 <= score[i] <= 106
score 中的所有值 互不相同
 */
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<string> findRelativeRanks(vector<int> &score)
    {
        size_t size = score.size();
        vector<string> ret(size);
        vector<int> nums(size);
        int i;
        for (i = 0; i < size; ++i)
            nums[i] = i;
        // 按得分降序
        std::sort(nums.begin(), nums.end(), [&score](const int &x, const int &y)
                  { return score[x] > score[y]; });
        for (i = 0; i < size; ++i)
        {
            // 编辑名次字符串
            string str;
            // 第一名
            if (i == 0)
                str = "Gold Medal";
            else if (i == 1)
                str = "Silver Medal";
            else if (i == 2)
                str = "Bronze Medal";
            else
                str = to_string(i + 1);
            // 将名次放到相应的位置，位置就是nums[i]
            ret[nums[i]] = str;
        }
        return ret;
    }
};

// int main()
// {
//     // vector<int> score = {5, 4, 3, 2, 1};
//     vector<int> score = {10,3,8,9,4};
//     Solution sl;
//     const auto &vec = sl.findRelativeRanks(score);
//     for_each(vec.begin(), vec.end(), [](const string &str)
//              { cout << str << " "; });
//     cout << endl;
//     return 0;
// }