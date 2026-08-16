//
// Created by Administrator on 2026/7/20.
//
/**
* 1260. 二维网格迁移
简单
相关标签
premium lock icon
相关企业
提示
给你一个 m 行 n 列的二维网格 grid 和一个整数 k。你需要将 grid 迁移 k 次。

每次「迁移」操作将会引发下述活动：

位于 grid[i][j]（j < n - 1）的元素将会移动到 grid[i][j + 1]。
位于 grid[i][n - 1] 的元素将会移动到 grid[i + 1][0]。
位于 grid[m - 1][n - 1] 的元素将会移动到 grid[0][0]。
请你返回 k 次迁移操作后最终得到的 二维网格。



示例 1：



输入：grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
输出：[[9,1,2],[3,4,5],[6,7,8]]
示例 2：



输入：grid = [[3,8,1,9],[19,7,2,5],[4,6,11,10],[12,0,21,13]], k = 4
输出：[[12,0,21,13],[3,8,1,9],[19,7,2,5],[4,6,11,10]]
示例 3：

输入：grid = [[1,2,3],[4,5,6],[7,8,9]], k = 9
输出：[[1,2,3],[4,5,6],[7,8,9]]


提示：

m == grid.length
n == grid[i].length
1 <= m <= 50
1 <= n <= 50
-1000 <= grid[i][j] <= 1000
0 <= k <= 100
 * @return
 */
#include <deque>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > shiftGrid(vector<vector<int> > &grid, int k) {
        int row = grid.size(), col = grid.at(0).size(), size = row * col, cnt, i, j;
        if (!(cnt = k % size))
            return grid;
        deque<int> contain;
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
                contain.push_back(grid[i][j]);
        while (cnt--) {
            contain.push_front(contain.back());
            contain.pop_back();
        }
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                grid[i][j] = contain.front();
                contain.pop_front();
            }
        }
        return grid;
    }
};

// int main() {
//     return 0;
// }
