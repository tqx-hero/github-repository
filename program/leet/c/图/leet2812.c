//
// Created by Administrator on 2026/7/1.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
* 2812. 找出最安全路径
中等
相关标签
premium lock icon
相关企业
提示
给你一个下标从 0 开始、大小为 n x n 的二维矩阵 grid ，其中 (r, c) 表示：

如果 grid[r][c] = 1 ，则表示一个存在小偷的单元格
如果 grid[r][c] = 0 ，则表示一个空单元格
你最开始位于单元格 (0, 0) 。在一步移动中，你可以移动到矩阵中的任一相邻单元格，包括存在小偷的单元格。

矩阵中路径的 安全系数 定义为：从路径中任一单元格到矩阵中任一小偷所在单元格的 最小 曼哈顿距离。

返回所有通向单元格 (n - 1, n - 1) 的路径中的 最大安全系数 。

单元格 (r, c) 的某个 相邻 单元格，是指在矩阵中存在的 (r, c + 1)、(r, c - 1)、(r + 1, c) 和 (r - 1, c) 之一。

两个单元格 (a, b) 和 (x, y) 之间的 曼哈顿距离 等于 | a - x | + | b - y | ，其中 |val| 表示 val 的绝对值。



示例 1：


输入：grid = [[1,0,0],[0,0,0],[0,0,1]]
输出：0
解释：从 (0, 0) 到 (n - 1, n - 1) 的每条路径都经过存在小偷的单元格 (0, 0) 和 (n - 1, n - 1) 。
示例 2：


输入：grid = [[0,0,1],[0,0,0],[0,0,0]]
输出：2
解释：
上图所示路径的安全系数为 2：
- 该路径上距离小偷所在单元格（0，2）最近的单元格是（0，0）。它们之间的曼哈顿距离为 | 0 - 0 | + | 0 - 2 | = 2 。
可以证明，不存在安全系数更高的其他路径。
示例 3：


输入：grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
输出：2
解释：
上图所示路径的安全系数为 2：
- 该路径上距离小偷所在单元格（0，3）最近的单元格是（1，2）。它们之间的曼哈顿距离为 | 0 - 1 | + | 3 - 2 | = 2 。
- 该路径上距离小偷所在单元格（3，0）最近的单元格是（3，2）。它们之间的曼哈顿距离为 | 3 - 3 | + | 0 - 2 | = 2 。
可以证明，不存在安全系数更高的其他路径。


提示：

1 <= grid.length == n <= 400
grid[i].length == n
grid[i][j] 为 0 或 1
grid 至少存在一个小偷
 * @return
 */
//回溯算法
//可以先遍历数组，找出小偷坐标，放到thief[][2]中，其中每一个元素都代表小偷的坐标x、y。
//当然最应该先判断起点和终点是否有小偷，有一个存在，则直接返回0.
//一次遍历完数组以后，将小偷位置坐标(x,y)二元组的数组遍历：
//新建n*n二元数组Manhattan[],按照每个小偷位置的坐标(x,y)计算每个坐标(a,b)的曼哈顿距离:|a-x|+|b-y|。
//从Manhattan[]的(0,0)位置开始每次选取周围值最大max的那个坐标，一直到(n-1,n-1),同时更新曼哈顿距离cur= min(cur,max)

typedef struct position {
    int pos[2];
} position;

void free_resources(position **thief, int thief_count, int **Manhattan, int gridSize) {
    //释放曼哈顿数组
    for (int i = 0; i < gridSize; i++)
        free(Manhattan[i]);
    free(Manhattan);
    //释放thief数组
    while (thief_count)
        free(thief[--thief_count]);
    free(thief);
}

static inline int min(int x, int y) {
    return x <= y ? x : y;
}

static inline int max(int x, int y) {
    return x >= y ? x : y;
}

void find_path(int **Manhattan, int gridSize, int x, int y, int cur_man, int *ret) {
    if (x >= gridSize || y >= gridSize)
        return;
    int dst = Manhattan[x][y];
    //如果曼哈顿距离为0，走不通
    if (!dst) {
        return;
    }
    cur_man = min(cur_man, dst);
    //走成功了，更新结果集ret
    if (x == gridSize - 1 && y == gridSize - 1) {
        *ret = max(*ret, cur_man);
        return;
    }
    //没走成功就继续往前走
    find_path(Manhattan, gridSize, x, y + 1, cur_man, ret);
    find_path(Manhattan, gridSize, x + 1, y, cur_man, ret);
    //如果两边都走不通，即cur_man=0，返回
}

int init_man_arr(int **Manhattan, int gridSize) {
    int i = 0, j;
    for (; i < gridSize; i++) {
        int *mc = malloc(gridSize * sizeof(int));
        if (!mc) {
            printf("%s\n", strerror(errno));
            return 0;
        }
        Manhattan[i] = mc;
    }
    for (i = 0; i < gridSize; i++)
        for (j = 0; j < gridSize; j++)
            Manhattan[i][j] = (gridSize - 1) << 1;
    return 1;
}

int init_thief_arr(int **grid, int gridSize, position **thief, int *thief_count) {
    int i = 0, j = 0;
    for (i = 0; i < gridSize; i++) {
        for (j = 0; j < gridSize; j++) {
            if (grid[i][j]) {
                //添加小偷的坐标二元组
                position *tf = calloc(1, sizeof(position));
                if (!tf) {
                    printf("%s\n", strerror(errno));
                    return 0;
                }
                tf->pos[0] = i;
                tf->pos[1] = j;
                thief[(*thief_count)++] = tf;
            }
        }
    }
    return 1;
}

void update_man_arr(int **Manhattan, int gridSize, position **thief, const int *thief_count) {
    int i, j, k;
    for (i = 0; i < *thief_count; i++) {
        for (k = 0; k < gridSize; k++) {
            for (j = 0; j < gridSize; j++)
                Manhattan[k][j] = min(abs(thief[i]->pos[0] - k) + abs(thief[i]->pos[1] - j), Manhattan[k][j]);
        }
    }
}

bool can_reach(int **grid, int gridSize) {
    int sum_rows = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++)
            sum_rows += grid[i][j];
        if (sum_rows == gridSize)
            return false;
        sum_rows = 0;
    }
    return true;
}

int maximumSafenessFactor(int **grid, int gridSize, int *gridColSize) {
    if (grid[0][0] || grid[gridSize - 1][gridSize - 1] || !can_reach(grid, *gridColSize))
        return 0;
    int ret = 0, thief_count = 0;
    position **thief = (position **) calloc(gridSize * gridSize, sizeof(position));
    int **Manhattan = malloc(gridSize * sizeof(int *));
    if (!thief || !Manhattan) {
        printf("%s\n", strerror(errno));
        ret = -1;
        goto go_free_resource;
    }
    //初始化曼哈顿结果集,最大值为2(n-1)
    if (!init_man_arr(Manhattan, gridSize) || !init_thief_arr(grid, gridSize, thief, &thief_count)) {
        ret = -1;
        goto go_free_resource;
    }
    //处理thief数组，遍历并计算每个二元组对应的坐标曼哈顿值
    //更新时要注意取曼哈顿数组与计算结果的最小值
    update_man_arr(Manhattan, gridSize, thief, &thief_count);
    //在遍历时当遇到相邻节点全为0时注意回溯即可
    find_path(Manhattan, gridSize, 0, 0, (gridSize - 1) << 1, &ret);
go_free_resource:
    free_resources(thief, thief_count, Manhattan, gridSize);
    return ret;
}

//

int main() {
    //[0,0,1],[0,0,0],[0,0,0]
    //grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
    // int arr1[] = {0, 0, 0, 1};
    // int arr2[] = {0, 0, 0, 0};
    // int arr3[] = {0, 0, 0, 0};
    // int arr4[] = {1, 0, 0, 0};


    // [0,1,1],[1,1,0],[1,1,0]]
    // int arr1[] = {0, 1, 1};
    // int arr2[] = {1, 1, 0};
    // int arr3[] = {1, 1, 0};

    //grid = [0,1,1],[1,1,1],[1,1,0]
    // int arr1[] = {0, 1, 1};
    // int arr2[] = {1, 1, 1};
    // int arr3[] = {1, 1, 0};

    //[0,0,1],[0,0,0],[0,0,0]
    int arr1[] = {0, 0, 1};
    int arr2[] = {0, 0, 0};
    int arr3[] = {0, 0, 0};

    // int arr1[] = {1, 0, 0};
    // int arr2[] = {0, 0, 0};
    // int arr3[] = {0, 0, 1};
    int *grid[] = {arr1, arr2, arr3};
    int size = 3;
    printf("%d\n", maximumSafenessFactor(grid, size, &size));
    return 0;
}
