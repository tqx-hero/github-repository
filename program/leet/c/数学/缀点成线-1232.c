/**
   1232. 缀点成线
   简单
   相关标签
   premium lock icon
   相关企业
   提示
   给定一个整数数组 coordinates ，其中 coordinates[i] = [x, y] ， [x, y] 表示横坐标为 x、纵坐标为 y 的点。请你来判断，这些点是否在该坐标系中属于同一条直线上。



   示例 1：



   输入：coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
   输出：true
   示例 2：



   输入：coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
   输出：false


   提示：

   2 <= coordinates.length <= 1000
   coordinates[i].length == 2
   -104 <= coordinates[i][0], coordinates[i][1] <= 104
   coordinates 中不含重复的点
  */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool checkStraightLine(int** coordinates, int coordinatesSize, int* coordinatesColSize) {
    int i;
    int subx,suby;
    //如果x轴相同或者y轴相同，相同
    //如果不相同，就计算两个坐标的(y2 - y1) / (x2 - x1),相同则返回相同，出现不同则失败
    subx = coordinates[1][0] - coordinates[0][0];
    suby = coordinates[1][1] - coordinates[0][1];
    for(i = 2 ; i < coordinatesSize && 
            (coordinates[i][1] - coordinates[i - 1][1]) * subx ==  (coordinates[i][0] - coordinates[i - 1][0]) * suby
            ; ++i);
    return i == coordinatesSize;
}

int main(){
    //[[-3,-14],[-4,-21],[2,21],[7,56],[3,28]]
    int v1[] = {-3,-14},v2[]={-4,-21},v3[] = {2,21},v4[] = {7,56},v5[] = {3,28};
    int *coordinates[] = {v1,v2,v3,v4,v5},returnSize = sizeof(v1) / sizeof(int);
    fprintf(stdout,"%d\n",checkStraightLine(coordinates,sizeof(coordinates) / sizeof(int*),&returnSize));
    exit(0);
}
