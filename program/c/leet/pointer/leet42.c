//
// Created by Administrator on 2026/6/26.
//
/**
* 42. 接雨水
困难
相关标签
premium lock icon
相关企业
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。



示例 1：



输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。
示例 2：

输入：height = [4,2,0,3,2,5]
输出：9


提示：

n == height.length
1 <= n <= 2 * 104
0 <= height[i] <= 105
 * @return
 */
//前缀和+双指针。
//先遍历数组计算每个位置的前缀和prefix[]
//定义双指针left、right，标志变量count、结果集ret。初始位置right始终是大于left，即初始right=left+1.查找left位置：
//满足条件a[right]<a[left]开始。即当a[right]>=a[left]时都不会存住雨水，所以必须严格小于才可以。
//定位left指针以后，count=1，right++，后面遍历如果都满足a[right]<=a[right-1] && count !=-1,count++,right++
//当遇到a[right]>a[right-1]，且count!=0时,count=-1，然后right++,
//直到再次满足a[right]<=a[right-1] && count ==-1。此时计算从left到right-1这段区域的雨水数量
//计算方式为这段区域的最大表示面积-这段区域已经存在的数据块数：
//最大面积 = min(a[left],a[right-1]) * (right-1-left-1)
//已经存在的数据块计算方式为前缀和相减，还要减去a[left],即：prefix[right-1] - prefix[left] -a[left]
//两者相减即为这段区域的雨水数，并入ret，left = right-1，count=1
//还需要先统计每个元素下一个更大元素的位置，如果有next下标且next>cur+1,则可以直接计算[cur,next]区间内的雨水
//如果没有next，则需要按照上面的算法进行计算
#include <stdio.h>
#include <stdlib.h>
#define STACKPTR(name) Stack* name

static inline int min(int x, int y) {
    return x <= y ? x : y;
}

static inline int max(int x, int y) {
    return x >= y ? x : y;
}

int trap(int *height, int heightSize) {
    int left_max[heightSize], right_max[heightSize];
    int i = 0;
    left_max[0] = height[0];
    for (i = 1; i < heightSize; i++)
        left_max[i] = max(left_max[i - 1], height[i]);
    right_max[heightSize - 1] = height[heightSize - 1];
    for (i = heightSize - 2; i >= 0; i--)
        right_max[i] = max(right_max[i + 1], height[i]);
    int ret = 0;
    for (i = 0; i < heightSize; i++) {
        if (height[i] >= left_max[i] || height[i] >= right_max[i])
            continue;
        ret += min(left_max[i], right_max[i]) - height[i];
    }
    return ret;
}

int main() {
    int height[] = {4, 2, 0, 3, 2, 5};
    // int height[] = {5, 4, 1, 2};
    // int height[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    printf("%d\n", trap(height, sizeof(height) / sizeof(int)));
    return 0;
}
