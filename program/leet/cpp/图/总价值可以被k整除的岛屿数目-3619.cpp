/**
 *3619. 总价值可以被 K 整除的岛屿数目
中等
相关标签
premium lock icon
相关企业
提示
给你一个 m x n 的矩阵 grid 和一个正整数 k。一个 岛屿 是由 正 整数（表示陆地）组成的，并且陆地间 四周 连通（水平或垂直）。

一个岛屿的总价值是该岛屿中所有单元格的值之和。

返回总价值可以被 k 整除 的岛屿数量。

 

示例 1:


输入: grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5

输出: 2

解释:

网格中包含四个岛屿。蓝色高亮显示的岛屿的总价值可以被 5 整除，而红色高亮显示的岛屿则不能。

示例 2:


输入: grid = [[3,0,3,0], [0,3,0,3], [3,0,3,0]], k = 3

输出: 6

解释:

网格中包含六个岛屿，每个岛屿的总价值都可以被 3 整除。

 

提示:

m == grid.length
n == grid[i].length
1 <= m, n <= 1000
1 <= m * n <= 105
0 <= grid[i][j] <= 106
1 <= k < = 106
 */
#include <vector>
#include <iostream>
using namespace std;
//使用走迷宫形式，遍历二维数组，当元素值大于0时，以他为起点往四周扩散，记录它周围的大于0的每个元素进行相加
//一直到周围全是0或者到边界。为了避免在递归遍历时重复计算，需要使用一个相同大小的空间来记录每个网格是否被访问过
//被访问过的网格给同一位置的网格标记
class Solution {
	int ret = 0;
	long long landsum = 0;
	size_t row,col;
	bool out_of_bound(int x,int y){
		if(x < 0 || x >= row || y <0 || y >= col)
			return true;
		return false;
	}

	void dfs(vector<vector<int>>& grid,vector<vector<int>> &visited,int x,int y){
		//如果坐标越界，或者坐标值为0(不是岛屿),或者该坐标已被访问过，直接返回
		if(out_of_bound(x,y) || grid[x][y] == 0 || visited[x][y])
			return;
		//将该坐标值放入当前岛屿面积landsum,并做访问标记
		landsum += grid[x][y];
		visited[x][y] = 1;
		//从该点开始进行上下左右递归扩散
		dfs(grid,visited,x,y + 1);
		dfs(grid,visited,x,y - 1);
		dfs(grid,visited,x + 1,y);
		dfs(grid,visited,x - 1,y);
	}
public:
    int countIslands(vector<vector<int>>& grid, int k) {
	    row = grid.size();
	    col = grid[0].size();
	    vector<vector<int>> visited(row,vector<int>(col,0));
	    int i,j;
	    for(i=0;i<row;++i){
		    for(j=0;j<col;++j){
			    landsum = 0;
			    dfs(grid,visited,i,j);
			   //扩散完了，计算岛屿面积是否能被dived整除
			   if(landsum && landsum % k == 0)
				ret++;
		    }
	    }
	    return ret;
    }
};

int main(){
	// grid = [[0,2,1,0,0],[0,5,0,0,5],[0,0,1,0,0],[0,1,4,7,0],[0,2,0,0,8]], k = 5
	vector<vector<int>> grid{
		vector<int>{0,2,1,0,0},
		vector<int>{0,5,0,0,5},
		vector<int>{0,0,1,0,0},
		vector<int>{0,1,4,7,0},
		vector<int>{0,2,0,0,8}
	};
	int k =5;
	Solution sl;
	cout << sl.countIslands(grid,k) << endl;
	return 0;
}
