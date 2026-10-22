//
// Created by Administrator on 2026/8/19.
//
/**
* 1386. 安排电影院座位
￼
中等
￼
相关标签
￼
相关企业
￼
提示
￼
如上图所示，电影院的观影厅中有 n 行座位，行编号从 1 到 n ，且每一行内总共有 10 个座位，列编号从 1 到 10 。
给定一个二维数组 reservedSeats ，其中 reservedSeats[i] = [rowi, seati] 表示第 rowi 行的座位 seati 已经被预定。
四人小组必须被安排在同一排的四个座位上。该小组可以坐在以下座位块之一：
• 座位 2, 3, 4, 5
• 座位 4, 5, 6, 7
• 座位 6, 7, 8, 9
只有当该块中的所有座位都 没有 被预订时，才能使用该块。每个座位 最多 只能分配给一个小组。
返回一个整数，表示可以分配的 最大 四人小组数量。 
示例 1：
输入：
n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
输出：
4
解释：
上图所示是最优的安排方案，总共可以安排 4 个家庭。蓝色的叉表示被预约的座位，橙色的连续座位表示一个 4 人家庭。
示例 2：
输入：
n = 2, reservedSeats = [[2,1],[1,8],[2,6]]
输出：
2
示例 3：
输入：
n = 4, reservedSeats = [[4,3],[1,4],[4,6],[1,7]]
输出：
4
  提示：
• 1 <= n <= 109
• 1 <= reservedSeats.length <= min(10 * n, 104)
• reservedSeats[i] == [rowi, seati]
• 1 <= rowi <= n
• 1 <= seati <= 10
• 所有 reservedSeats[i] 都是互不相同的。
 * @return
 */
#include <unordered_map>
#include <vector>
#include <array>
#include <iostream>
using namespace std;

//n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
class Solution {
public:
    //使用位运算，进行判断座位是否可用
    int maxNumberOfFamilies(int n, vector<vector<int> > &reservedSeats) {
        int left = 15 << 4, middle = 15 << 2, right = 15;
        unordered_map<int, vector<int> > reservedSetCache;
        //统计每一行所占座位情况
        for (auto &rs: reservedSeats)
            reservedSetCache[rs[0]].push_back(rs[1]);
        int cnt = (n - static_cast<int>(reservedSetCache.size())) << 1;
        array<int, 3> contains{0};
        for (auto &pair: reservedSetCache) {
            contains.fill(0);
            auto &list = pair.second;
            int totalNum = 0;
            for (int rowNum: list) {
                if (rowNum == 1 || rowNum == 10)
                    continue;
                totalNum |= 1 << (9 - rowNum);
            }
            if (!(left & totalNum))
                contains[0] = 1;
            if (!(middle & totalNum))
                contains[1] = 1;
            if (!(right & totalNum))
                contains[2] = 1;
            int res = contains[0] + contains[1] + contains[2];
            cnt += res == 3 ? 2 : res == 0 ? 0 : 1;
        }
        return cnt;
    }

    //用set集合做哈希表，然后进行判空
    // int maxNumberOfFamilies(int n, vector<vector<int> > &reservedSeats) {
    //     unordered_set<int> set1{2, 3, 4, 5}, set2{4, 5, 6, 7}, set3{6, 7, 8, 9};
    //     unordered_map<int, vector<int> > reservedSetCache;
    //     //统计每一行所占座位情况
    //     for (auto &rs: reservedSeats)
    //         reservedSetCache[rs[0]].push_back(rs[1]);
    //     int reservedRowSize = static_cast<int>(reservedSetCache.size());
    //     int cnt = (n - reservedRowSize) << 1;
    //     array<int, 3> contains{0};
    //     for (auto &pair: reservedSetCache) {
    //         contains.fill(0);
    //         auto &list = pair.second;
    //         for (int rowNum: list) {
    //             if (set1.count(rowNum))
    //                 contains[0] = 1;
    //             if (set2.count(rowNum))
    //                 contains[1] = 1;
    //             if (set3.count(rowNum))
    //                 contains[2] = 1;
    //         }
    //         int res = contains[0] + contains[1] + contains[2];
    //         cnt += res == 3 ? 0 : res == 0 ? 2 : 1;
    //     }
    //     return cnt;
    // }
};

// int main() {
//     int n = 3;
//     vector<vector<int> > reservedSeats = {{1, 2}, {1, 3}, {1, 8}, {2, 6}, {3, 1}, {3, 10}};
//     Solution sl;
//     cout << sl.maxNumberOfFamilies(n, reservedSeats) << endl;
//     return 0;
// }
