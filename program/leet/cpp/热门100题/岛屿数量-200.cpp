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
#include <algorithm>

using namespace std;

//TODO
class Solution {
    int row_size = 0, col_size = 0;

    bool check_postion_valid(int x, int y) {
        if (x < 0 || x >= row_size || y < 0 || y >= col_size)
            return false;
        return true;
    }

    //检查坐标是否已被标记
    bool get_round_target(vector<vector<bool> > &visited, int x, int y) {
        if (!check_postion_valid(x, y))
            return false;
        return visited[x][y];
    }

    void dfs(vector<vector<char> > &grid, vector<vector<bool> > &visited, int &ret, int x, int y) {
        //检查坐标是否合法
        if (!check_postion_valid(x, y) || visited[x][y] || grid[x][y] == '0')
            return;
        //设置该点位被标记
        visited[x][y] = true;
        //检查四周是否都被访问过
        //四周都没有被访问过，说明它为新的岛屿，增加计数
        if (!get_round_target(visited, x - 1, y) && !get_round_target(visited, x + 1, y)
            && !get_round_target(visited, x, y - 1) && !get_round_target(visited, x, y + 1))
            ret++;
        //深度遍历，走迷宫形式标记它周围的可能连接的岛屿
        dfs(grid, visited, ret, x - 1, y);
        dfs(grid, visited, ret, x + 1, y);
        dfs(grid, visited, ret, x, y - 1);
        dfs(grid, visited, ret, x, y + 1);
    }

public:
    int numIslands(vector<vector<char> > &grid) {
        //需要采用回溯算法，深度遍历优先，走迷宫方式
        row_size = static_cast<int>(grid.size());
        col_size = static_cast<int>(grid[0].size());
        //创建一个访问数组，供后续深度遍历时判断
        vector<vector<bool> > visited(row_size);
        int ret = 0, x, y;
        for (x = 0; x < row_size; ++x) {
            vector<bool> vc(col_size, false);
            visited[x] = vc;
        }
        for (x = 0; x < row_size; ++x)
            for (y = 0; y < col_size; ++y)
                dfs(grid, visited, ret, x, y);
        return ret;
    }
};

/* 
测试不通过：
结果=2，答案=1
[1,0,1,1,1]
[1,0,1,0,1]
[1,1,1,0,1]
*/
// int main() {
//     vector<vector<char> > grid{
//         {
//             1, 0, 1, 1, 1
//         },
//         {
//             1, 0, 1, 0, 1
//         },
//         {
//             1, 1, 1, 0, 1
//         }
//     };
//     // vector<vector<char> > grid{
//     //     {'1', '1', '1', '1', '0'},
//     //     {'1', '1', '0', '1', '0'},
//     //     {'1', '1', '0', '0', '0'},
//     //     {'0', '0', '0', '0', '0'}
//     // };
//     Solution sl;
//     cout << sl.numIslands(grid) << endl;
//     return 0;
// }
