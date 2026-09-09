//
// Created by 田庆新 on 2026/9/9.
//
/**
* 994. 腐烂的橘子
中等
相关标签
premium lock icon
相关企业
在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：

值 0 代表空单元格；
值 1 代表新鲜橘子；
值 2 代表腐烂的橘子。
每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。

返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。



示例 1：



输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4
示例 2：

输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
示例 3：

输入：grid = [[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。


提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] 仅为 0、1 或 2
 * @return
 */
#include <queue>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    int row_size = 0, col_size = 0;

    int change_around(vector<vector<int> > &grid, int x, int y, queue<pair<int, int> > &orange_queue) {
        if (x < 0 || x >= row_size || y < 0 || y >= col_size || grid[x][y] != 1)
            return 0;
        //感染好橘子
        grid[x][y] = 2;
        orange_queue.emplace(x, y);
        return 1;
    }

public:
    int orangesRotting(vector<vector<int> > &grid) {
        //广度优先。维护一个队列，存放腐烂橘子的坐标。
        //遍历集合，将值=2的坐标放到队列。
        //遍历队列，将队列中每个坐标的四周等于1的坐标都设置成2，同时将1->2的坐标放到队列。
        //每轮队列遍历结束，增加一次计数。
        //当队列为空时，表明所有橘子该腐烂的都已经腐烂，此时查看网格中是否还有完好的橘子，有返回-1，没有就返回次数
        queue<pair<int, int> > orange_queue;
        row_size = static_cast<int>(grid.size()), col_size = static_cast<int>(grid[0].size());
        int times = 0, good_cnt = 0, x, y;
        //遍历数组，统计出初始节点腐烂橘子的坐标，以及完好橘子的个数
        for (x = 0; x < row_size; ++x) {
            for (y = 0; y < col_size; ++y) {
                int val = grid[x][y];
                if (val == 1)
                    good_cnt++;
                else if (val == 2)
                    orange_queue.emplace(x, y);
            }
        }
        //有腐烂橘子，遍历每个坐标，将它的四周坐标值=1的全部变成2,放入队列
        int queue_size = 0;
        while ((queue_size = static_cast<int>(orange_queue.size())) != 0 && good_cnt) {
            //腐烂橘子感染
            while (queue_size--) {
                x = orange_queue.front().first;
                y = orange_queue.front().second;
                //将以(x,y)为中心的四周全部感染
                int change_cnt = 0;
                change_cnt += change_around(grid, x - 1, y, orange_queue);
                change_cnt += change_around(grid, x + 1, y, orange_queue);
                change_cnt += change_around(grid, x, y - 1, orange_queue);
                change_cnt += change_around(grid, x, y + 1, orange_queue);
                good_cnt -= change_cnt;
                orange_queue.pop();
            }
            //一轮感染结束，增加一次计数
            ++times;
        }
        return good_cnt ? -1 : times;
    }
};

// int main() {
//     //[[2,1,1],[1,1,0],[0,1,1]]
//     // vector<vector<int> > grid{
//     //     {2, 1, 1},
//     //     {1, 1, 0},
//     //     {0, 1, 1}
//     // };
//     //[[2,1,1],[0,1,1],[1,0,1]]
//     // vector<vector<int> > grid{
//     //     {2, 1, 1},
//     //     {0, 1, 1},
//     //     {1, 0, 1}
//     // };
//     //[0,2]
//     vector<vector<int> > grid{
//         {1, 0, 2}
//     };
//     Solution sl;
//     cout << sl.orangesRotting(grid) << endl;
//     return 0;
// }
