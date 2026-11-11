/**
  1030. 距离顺序排列矩阵单元格
  简单
  相关标签
  premium lock icon
  相关企业
  给定四个整数 rows ,   cols ,  rCenter 和 cCenter 。有一个 rows x cols 的矩阵，你在单元格上的坐标是 (rCenter, cCenter) 。

  返回矩阵中的所有单元格的坐标，并按与 (rCenter, cCenter) 的 距离 从最小到最大的顺序排。你可以按 任何 满足此条件的顺序返回答案。

  单元格(r1, c1) 和 (r2, c2) 之间的距离为|r1 - r2| + |c1 - c2|。



  示例 1：

  输入：rows = 1, cols = 2, rCenter = 0, cCenter = 0
  输出：[[0,0],[0,1]]
  解释：从 (r0, c0) 到其他单元格的距离为：[0,1]
  示例 2：

  输入：rows = 2, cols = 2, rCenter = 0, cCenter = 1
  输出：[[0,1],[0,0],[1,1],[1,0]]
  解释：从 (r0, c0) 到其他单元格的距离为：[0,1,1,2]
  [[0,1],[1,1],[0,0],[1,0]] 也会被视作正确答案。
  示例 3：

  输入：rows = 2, cols = 3, rCenter = 1, cCenter = 2
  输出：[[1,2],[0,2],[1,1],[0,1],[1,0],[0,0]]
  解释：从 (r0, c0) 到其他单元格的距离为：[0,1,1,2,2,3]
  其他满足题目要求的答案也会被视为正确，例如 [[1,2],[1,1],[0,2],[1,0],[0,1],[0,0]]。


  提示：

  1 <= rows, cols <= 100
  0 <= rCenter < rows
  0 <= cCenter < cols
 */
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
#define  VALID_ADD(x,y) if(valid(x,y) && !visited[x][y])    \
{                       \
    pos_que.emplace(x, y);  \
    visited[x][y] = 1;  \
}
class Solution {

    int rows_sz,cols_sz;

    bool valid(int x,int y){
        if(x < 0 || x >= rows_sz || y < 0 || y >= cols_sz)
            return false;
        return true;
    }

    public:
    vector<vector<int>> allCellsDistOrder(int rows, int cols, int rCenter, int cCenter) {
        vector<vector<int>> ret;
        ret.reserve(rows * cols);
        rows_sz = rows;
        cols_sz = cols;
        vector<vector<int>> visited(rows,vector<int>(cols,0));
        queue<pair<int,int>> pos_que;
        pos_que.emplace(rCenter,cCenter);
        visited[rCenter][cCenter] = 1;
        size_t qsz,i;
        int x,y;
        while(qsz = pos_que.size()){
            for(i = 0;i < qsz;++i){
                //取出坐标，将他添加到数组
                x = pos_que.front().first;
                y = pos_que.front().second;
                ret.push_back(vector<int>{x,y});
                pos_que.pop();
                //找到与他相邻的点
                VALID_ADD(x - 1,y)
                    VALID_ADD(x + 1,y)
                    VALID_ADD(x,y - 1)
                    VALID_ADD(x,y + 1)
            }
        }
        return ret;
    }
};


int main(){
    int rows = 2, cols = 2, rCenter = 0, cCenter = 1;
    Solution sl;
    const auto& vc = sl.allCellsDistOrder(rows,cols,rCenter,cCenter);
    for(int i = 0;i < vc.size();++i){
        for(int j = 0;j < 2;++j){
            cout << vc[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}
