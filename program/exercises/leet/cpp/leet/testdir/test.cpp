/**
 * 1401. 圆和矩形是否有重叠
中等
相关标签
premium lock icon
相关企业
提示
给你一个以 (radius, xCenter, yCenter) 表示的圆和一个与坐标轴平行的矩形 (x1, y1, x2, y2) ，其中 (x1, y1) 是矩形左下角的坐标，而 (x2, y2) 是右上角的坐标。

如果圆和矩形有重叠的部分，请你返回 true ，否则返回 false 。

换句话说，请你检测是否 存在 点 (xi, yi) ，它既在圆上也在矩形上（两者都包括点落在边界上的情况）。



示例 1 ：


输入：radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1
输出：true
解释：圆和矩形存在公共点 (1,0) 。
示例 2 ：

输入：radius = 1, xCenter = 1, yCenter = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1
输出：false
示例 3 ：


输入：radius = 1, xCenter = 0, yCenter = 0, x1 = -1, y1 = 0, x2 = 0, y2 = 1
输出：true


提示：

1 <= radius <= 2000
-104 <= xCenter, yCenter <= 104
-104 <= x1 < x2 <= 104
-104 <= y1 < y2 <= 104
 */
// 计算圆的中心与矩形四个顶点的距离，
// 圆心在矩形上下方时，相切的最远距离= sqart(r^2 + ((x2-x1) /2)^2 ),注意要转成double
// 圆心在矩形左右方向，相切最远 = sqart(r^2 + ((y2-y1) /2) ^2)
// 分别计算各点与圆心的距离，如果有一个小于等于以上这个距离，就有重叠
//特别情况，如果圆心在矩形边界范围内，直接返回true
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

class Solution
{
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2)
    {
        double max_dst, min_dst;
        int x_dst, y_dst;
        if (xCenter <= x1 || xCenter >= x2)
        {
            max_dst = sqrt(pow(radius, 2) + pow((y2 - y1) / 2.0, 2));
            // 圆心在矩形左半边
            y_dst = min(abs(y1 - yCenter), abs(y2 - yCenter));
            x_dst = min(abs(x1 - xCenter), abs(x2 - xCenter));
        }
        else
        {
            // 圆心在x1-x2之间
            // 先判断圆心是否在y1-y2之间,如果存在，必然有重叠部分
            if (yCenter >= y1 && yCenter <= y2)
                return true;
            max_dst = sqrt(pow(radius, 2) + pow((x2 - x1) / 2.0, 2));
            x_dst = min(abs(x1 - xCenter), abs(x2 - xCenter));
            y_dst = min(abs(y1 - yCenter), abs(y2 - yCenter));
        }
        min_dst = sqrt(pow(x_dst, 2) + pow(y_dst, 2));
        return min_dst <= max_dst;
    }
};

// int main()
// {
//     // int radius = 1, xCenter = 0, yCenter = 0, x1 = 1, y1 = -1, x2 = 3, y2 = 1;
//     int radius = 1, xCenter = 1, yCenter = 1, x1 = 1, y1 = -3, x2 = 2, y2 = -1;
//     Solution sl;
//     cout << sl.checkOverlap(radius, xCenter, yCenter, x1, y1, x2, y2) << endl;
//     return 0;
// }