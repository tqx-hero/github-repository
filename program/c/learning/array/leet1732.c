//
// Created by Administrator on 2026/6/19.
//
/**
* 1732. 找到最高海拔
简单
相关标签
premium lock icon
相关企业
提示
有一个自行车手打算进行一场公路骑行，这条路线总共由 n + 1 个不同海拔的点组成。自行车手从海拔为 0 的点 0 开始骑行。

给你一个长度为 n 的整数数组 gain ，其中 gain[i] 是点 i 和点 i + 1 的 净海拔高度差（0 <= i < n）。请你返回 最高点的海拔 。



示例 1：

输入：gain = [-5,1,5,0,-7]
输出：1
解释：海拔高度依次为 [0,-5,-4,1,1,-6] 。最高海拔为 1 。
示例 2：

输入：gain = [-4,-3,-2,-1,4,3,2]
输出：0
解释：海拔高度依次为 [0,-4,-7,-9,-10,-6,-3,-1] 。最高海拔为 0 。


提示：

n == gain.length
1 <= n <= 100
-100 <= gain[i] <= 100

 * @return
 */
#define  MAX(x,y) ((x) >=(y) ? (x) :(y))
#include <stdio.h>

int largestAltitude(int *gain, int gainSize) {
    int cur = 0, max = 0, i = 0;
    for (; i < gainSize; i++) {
        cur += *(gain + i);
        max = MAX(max, cur);
    }
    return max;
}

int main() {
    int arr[]={-4,-3,-2,-1,4,3,2};
    printf("%d \n",largestAltitude(arr,5));
    return 0;
}
