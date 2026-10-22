//
// Created by Administrator on 2026/8/3.
//
/**
* 1499. 满足不等式的最大值
困难
相关标签
premium lock icon
相关企业
提示
给你一个数组 points 和一个整数 k 。数组中每个元素都表示二维平面上的点的坐标，并按照横坐标 x 的值从小到大排序。也就是说 points[i] = [xi, yi] ，并且在 1 <= i < j <= points.length 的前提下， xi < xj 总成立。

请你找出 yi + yj + |xi - xj| 的 最大值，其中 |xi - xj| <= k 且 1 <= i < j <= points.length。

题目测试数据保证至少存在一对能够满足 |xi - xj| <= k 的点。



示例 1：

输入：points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
输出：4
解释：前两个点满足 |xi - xj| <= 1 ，代入方程计算，则得到值 3 + 0 + |1 - 2| = 4 。第三个和第四个点也满足条件，得到值 10 + -10 + |5 - 6| = 1 。
没有其他满足条件的点，所以返回 4 和 1 中最大的那个。
示例 2：

输入：points = [[0,0],[3,0],[9,2]], k = 3
输出：3
解释：只有前两个点满足 |xi - xj| <= 3 ，代入方程后得到值 0 + 0 + |0 - 3| = 3 。


提示：

2 <= points.length <= 105
points[i].length == 2
-108 <= xi, yi <= 108
0 <= k <= 2 * 108
对于所有的 1 <= i < j <= points.length，均有 xi < xj。
xi 构成一个严格递增序列。
 * @return
 */
#include <vector>
#include <deque>
#include <iostream>
using namespace std;

class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int> > &points, int k) {
        int result = INT_MIN, i, size = static_cast<int>(points.size());
        deque<int> idxDeque;
        for (i = 0; i < size; i++) {
            int curX = points[i][0];
            int curY = points[i][1];
            while (!idxDeque.empty()) {
                int idx = idxDeque.front();
                int x = points[idx][0], xAbs;
                //如果找到了，计算统计值，并更新result
                if ((xAbs = curX - x) <= k) {
                    result = max(result, xAbs + points[idx][1] + curY);
                    break;
                }
                //如果2个x坐标不在区间k内，弹出队头，直到找到在k区间内的横坐标x
                idxDeque.pop_front();
            }
            //统计结束后需要把队尾贡献值小于等于当前元素的idx弹出
            //贡献值：可以理解为当前数对[a,b]与队尾数对[c,d]谁对于后面的数对贡献多
            //由于points集合的x坐标严格递增，所以队尾的c必定小于a，那么对于横坐标来说，队尾必定比当前数对贡献大，具体大：a-c
            //同样可以计算纵坐标y的贡献值，当前数对相对于队尾的贡献值为:b-d.
            //比较这两个相对贡献值，如果 b-d >= a-c,说明当前数对比队尾贡献值更大，对于之后的计算:yi+yj+|xi-xj|,必然大于队尾
            //此时需要弹出队尾。迭代直到队列为空或者队尾贡献大于当前数对，将当前数对下标放入队尾
            while (!idxDeque.empty()) {
                int idx = idxDeque.back();
                if (curY - points[idx][1] >= curX - points[idx][0])
                    idxDeque.pop_back();
                else
                    break;
            }
            idxDeque.push_back(i);
        }
        return result;
    }
};

// int main() {
//     vector<vector<int> > points{{0, 0}, {3, 0}, {9, 2}};
//     int k = 3;
//     // vector<vector<int> > points{{1, 3}, {2, 0}, {5, 10}, {6, -10}};
//     // int k = 1;
//     Solution sl;
//     cout << sl.findMaxValueOfEquation(points, k) << endl;
//     return 0;
// }
