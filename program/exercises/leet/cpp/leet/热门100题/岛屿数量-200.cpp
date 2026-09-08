/**
 * 200. 岛屿数量
中等
相关标签
premium lock icon
相关企业
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

 

示例 1：

输入：grid = [
  ['1','1','1','1','0'],
  ['1','1','0','1','0'],
  ['1','1','0','0','0'],
  ['0','0','0','0','0']
]
输出：1
示例 2：

输入：grid = [
  ['1','1','0','0','0'],
  ['1','1','0','0','0'],
  ['0','0','1','0','0'],
  ['0','0','0','1','1']
]
输出：3
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 300
grid[i][j] 的值为 '0' 或 '1'
 */
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;
//TODO
class Solution {
    struct Entry {
        int x, y;
        mutable bool visited;

        Entry(int x, int y, bool visited = false) : x(x), y(y), visited(visited) {
        }

        bool operator==(const Entry &other) const noexcept {
            return this->x == other.x && this->y == other.y;
        }
    };

    struct EntryHash {
        static void hash_combine(std::size_t &seed, const int &val) noexcept {
            hash<int> hasher;
            seed ^= hasher(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }

        size_t operator()(const Entry &x) const noexcept {
            size_t seed = 0;
            hash_combine(seed, x.x);
            hash_combine(seed, x.y);
            return seed;
        }
    };

    void update_around(int &target_cnt, Entry &entry, unordered_set<Entry, EntryHash> &lands_set) {
        unordered_set<Entry, EntryHash>::iterator cur_it;
        if ((cur_it = lands_set.find(entry)) != lands_set.end()) {
            //如果四周坐标已被标记，增加标记计数，该计数为0时表示四周没有坐标被标记
            target_cnt = cur_it->visited ? target_cnt + 1 : target_cnt;
            cur_it->visited = true;
        }
    }

public:
    int numIslands(vector<vector<char> > &grid) {
        //哈希表，存放的数对是坐标<x,y>，用于记录已经存在的岛屿坐标
        unordered_set<Entry, EntryHash> lands_set;
        int i, j, row_size = static_cast<int>(grid.size()), col_size = static_cast<int>(grid[0].size());
        vector<pair<int,int>> cut_down_set;
        //将岛屿坐标放到哈希表中
        for (i = 0; i < row_size; ++i) {
            for (j = 0; j < col_size; j++) {
                if (grid[i][j] == '1'){
                    lands_set.emplace(i, j);
                    cut_down_set.emplace_back(i,j);
                }
            }
        }
        //遍历哈希表每个坐标如果它的四周坐标有一个存在在哈希表中，就将他视作一个岛屿。
        //否则就增加一个岛屿计数
        if (lands_set.empty())
            return 0;
        int cnt = 0;
        for (auto &en: cut_down_set) {
            int cur_x = en.first, cur_y = en.second;
            //1、如果该坐标还未被标记，需要查看四周是否有标记的坐标。
            //如果有，说明该坐标与已记录的岛屿相连，不能增加计数
            //如果四周没有被标记，计数+1
            //2、如果该坐标已被标记，直接标记四周还未标记的坐标
            //无论上述情况是哪种，都需要把四周存在的岛屿全部标记
            int target_cnt = 0;
            Entry entry{cur_x - 1, cur_y};
            update_around(target_cnt, entry, lands_set);
            entry.x = cur_x + 1;
            update_around(target_cnt, entry, lands_set);
            entry.x = cur_x;
            entry.y = cur_y - 1;
            update_around(target_cnt, entry, lands_set);
            entry.y = cur_y + 1;
            update_around(target_cnt, entry, lands_set);
            //只有当前节点未被标记且四周也未被标记时，才可以增加有效计数
            unordered_set<Entry, EntryHash>::iterator cur_it = lands_set.find(Entry{cur_x,cur_y});
            if (cur_it->visited == false && target_cnt == 0)
                cnt++;
            //最后都需要把当前坐标标记
            cur_it->visited = true;
        }
        return cnt;
    }
};
/* 
测试不通过：
结果=2，答案=1
[1,0,1,1,1]
[1,0,1,0,1]
[1,1,1,0,1]
*/
int main() {
    vector<vector<char> > grid{
        {'1', '1', '1', '1', '0'},
        {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'}
    };
    Solution sl;
    cout << sl.numIslands(grid) << endl;
    return 0;
}
