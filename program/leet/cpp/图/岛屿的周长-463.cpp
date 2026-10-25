
/**
 *463. 岛屿的周长
简单
相关标签
premium lock icon
相关企业
给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。

网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。

岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。

 

示例 1：



输入：grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
输出：16
解释：它的周长是上面图片中的 16 个黄色的边
示例 2：

输入：grid = [[1]]
输出：4
示例 3：

输入：grid = [[1,0]]
输出：4
 

提示：

row == grid.length
col == grid[i].length
1 <= row, col <= 100
grid[i][j] 为 0 或 1
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//第一遍遍历二维数组，统计方格值为1的个数，grid_cnt
//第二遍遍历，当出现1的时候。
//查看它的右边与下面相邻的方格是否为1：
//如果为1，记1，最后计算出重复边repeat_cnt
//使用grid_cnt * 4 - repeat_cnt *2,就是结果
class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
	int grid_cnt = 0,repeat_cnt = 0;
	size_t row = grid.size(),col = grid[0].size();
	//1、统计1的个数
	for_each(grid.begin(),grid.end(),[&grid_cnt](const vector<int>& vc){
			for_each(vc.begin(),vc.end(),[&grid_cnt](const int & num){
					grid_cnt += num;
					});
			});
	//统计重复边的个数
	int i,j;
	for(i=0;i < row;++i){
		for(j = 0;j < col;++j){
			if(grid[i][j] == 1){
				//方格值为1，查看右边与下边方格值是否为1
				//右边方格
				if(j + 1 < col && grid[i][j+1])
					repeat_cnt++;
				//下边方格
				if(i + 1 < row && grid[i+1][j])
					repeat_cnt++;	
			}
		}
	}
	return grid_cnt * 4 - repeat_cnt * 2;
    }
};

int main(){
	vector<vector<int>> grid{
		{0,1,0,0},
		{1,1,1,0},
		{0,1,0,0},
		{1,1,0,0}
	};
	Solution sl;
	cout << sl.islandPerimeter(grid) << endl;
	return 0;
}
