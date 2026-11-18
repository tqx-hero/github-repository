/**
1351. 统计有序矩阵中的负数
简单
相关标签
premium lock icon
相关企业
提示
给你一个 m * n 的矩阵 grid，矩阵中的元素无论是按行还是按列，都以非严格递减顺序排列。 请你统计并返回 grid 中 负数 的数目。

 

示例 1：

输入：grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
输出：8
解释：矩阵中共有 8 个负数。
示例 2：

输入：grid = [[3,2],[1,0]]
输出：0
 

提示：

m == grid.length
n == grid[i].length
1 <= m, n <= 100
-100 <= grid[i][j] <= 100
 

进阶：你可以设计一个时间复杂度为 O(n + m) 的解决方案吗？
  */
#include <stdio.h>
#include <stdlib.h>

int countNegatives(int** grid, int gridSize, int* gridColSize) {
    int ret = 0;
    int i,j;
    for(i = 0,j = gridColSize[i] - 1;j >= 0 && i < gridSize;)
    {
        if(grid[i][j] < 0)
        {
            ret += gridSize - i;
            j--;
        }else
            i++;
    }
    return ret;
}

int main(){
    int* grid[] = {(int[]){4, 3, 2, -1}, (int[]){3, 2, 1, -1}, (int[]){1, 1, -1, -2}, (int[]){-1, -1, -2, -3}};
    int gridSize = 4;
    int gridColSize[] = {4, 4, 4, 4};
    fprintf(stdout,"%d\n",countNegatives(grid,gridSize,gridColSize));
    exit(0);
}
