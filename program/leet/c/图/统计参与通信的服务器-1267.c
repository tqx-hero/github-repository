
/**

1267. 统计参与通信的服务器
中等
相关标签
premium lock icon
相关企业
提示
这里有一幅服务器分布图，服务器的位置标识在 m * n 的整数矩阵网格 grid 中，1 表示单元格上有服务器，0 表示没有。

如果两台服务器位于同一行或者同一列，我们就认为它们之间可以进行通信。

请你统计并返回能够与至少一台其他服务器进行通信的服务器的数量。

 

示例 1：



输入：grid = [[1,0],[0,1]]
输出：0
解释：没有一台服务器能与其他服务器进行通信。
示例 2：



输入：grid = [[1,0],[1,1]]
输出：3
解释：所有这些服务器都至少可以与一台别的服务器进行通信。
示例 3：



输入：grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
输出：4
解释：第一行的两台服务器互相通信，第三列的两台服务器互相通信，但右下角的服务器无法与其他服务器通信。
 

提示：

m == grid.length
n == grid[i].length
1 <= m <= 250
1 <= n <= 250
grid[i][j] == 0 or 1
 */
#include <stdio.h>
#include <stdlib.h>
//先申请与数组相同大小的内存，用来存放每个点是否被标记
//再按照逐行遍历，查找到第一个1坐标，往后相同行与相同列，每找到一个值为1坐标，标记那个坐标，最后如果能找到起码1个点，把当前坐标标记
//最后遍历申请的数组，返回它的所有元素和

int **mk_cache(int row_size,int col_size){
	int** cache,*col_cache;
	int i;
	cache = (int**)malloc(row_size * sizeof(int *));
	if(!cache){
		perror("malloc error");
		exit(1);
	}
	//申请列空间
	for(i = 0;i < row_size;++i){
		col_cache = calloc(col_size,sizeof(int));
		if(!col_cache){
			perror("calloc() error");
			exit(1);
		}
		cache[i] = col_cache;
	}
	return cache;
}

int countServers(int** grid, int gridSize, int* gridColSize) {
	int** cache;
	int i,j,tempj,tempi;
	int cnt,sumval;
	cache = mk_cache(gridSize,*gridColSize);
	//遍历二维数组
	for(i = 0;i < gridSize;++i){
		for(j = 0;j < *gridColSize;++j){
			//找到值为1的下标
			if(grid[i][j]){
				cnt = 0;
				//往后遍历
				for(tempj = j + 1;tempj < *gridColSize;++tempj){
					if(grid[i][tempj]){
						cache[i][tempj] = 1;
						cnt++;
					}
				}
				//往下遍历
				for(tempi = i + 1;tempi < gridSize;++tempi){
					if(grid[tempi][j]){
						cache[tempi][j] = 1;
						cnt++;
					}
				}
				//判断cnt是否大于0，大于0则标记该坐标
				if(cnt)
					cache[i][j] = 1;
			}
		}
	}
	sumval = 0;
	//统计cache的元素之和，就是数量
	for(i = 0;i < gridSize;++i){
		for(j = 0;j < *gridColSize;++j)
			sumval += cache[i][j];
		free(cache[i]);
		cache[i] = NULL;
	}
	free(cache);
	return sumval;
}

int main(){
	int g1[] = {1,0},g2[] = {1,1};
//	grid = [[1,0],[1,1]]
	int *grid[] = {g1,g2};
	int gridColSize = sizeof(g1) / sizeof(int);
	fprintf(stdout,"%d\n",countServers(grid,sizeof(grid) / sizeof(grid[0]),&gridColSize));
	return 0;
}
