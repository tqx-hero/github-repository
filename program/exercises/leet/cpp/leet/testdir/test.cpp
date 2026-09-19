/**
 * class Solution
{
public:
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2)
    {
        //定义max_dst为相切时的距离，min_dst为实际圆心到最近矩形顶点的距离
        double max_dst, min_dst;
        //x_dst为圆心到矩形最近顶点的x轴距离，y_dst为y轴距离
        int x_dst, y_dst;
        //圆心在矩形左右两边，横坐标超过矩形左右边界
        if (xCenter <= x1 || xCenter >= x2)
        {
            max_dst = sqrt(pow(radius, 2) + pow((y2 - y1) / 2.0, 2));
            // 圆心在矩形左半边
            y_dst = min(abs(y1 - yCenter), abs(y2 - yCenter));
            x_dst = min(abs(x1 - xCenter), abs(x2 - xCenter));
        }
        else
        //圆心在矩形上下部分，在x1-x2之间
        {
            // 先判断圆心是否在y1-y2之间,如果存在，为包含关系
            if (yCenter >= y1 && yCenter <= y2)
                return true;
            max_dst = sqrt(pow(radius, 2) + pow((x2 - x1) / 2.0, 2));
            x_dst = min(abs(x1 - xCenter), abs(x2 - xCenter));
            y_dst = min(abs(y1 - yCenter), abs(y2 - yCenter));
        }
        min_dst = sqrt(pow(x_dst, 2) + pow(y_dst, 2));
        //最近距离小于等于相切距离，图形就有重叠
        return min_dst <= max_dst;
    }
};
 */
#include <iostream>
using namespace std;

class Solution
{
public:
    bool isPowerOfFour(int n)
    {
        return n > 0 && (n & (n - 1)) == 0 && (n & 0xAAAAAAAA) == 0;
    }
};

// int main()
// {
//     int n = 12;
//     Solution sl;
//     cout << sl.isPowerOfFour(n) << endl;
//     return 0;
// }