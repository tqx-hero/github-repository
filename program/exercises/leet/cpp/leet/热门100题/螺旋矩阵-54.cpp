//
// Created by 田庆新 on 2026/9/2.
//
/**
* 54. 螺旋矩阵
中等
相关标签
premium lock icon
相关企业
提示
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。



示例 1：


输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
示例 2：


输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]


提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 10
-100 <= matrix[i][j] <= 100
 * @return
 */
#include <algorithm>
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int> > &matrix) {
        int row_size = static_cast<int>(matrix.size()), col_size = static_cast<int>(matrix[0].size()),
                total_size = row_size * col_size,
                row_left = 0, row_right = row_size - 1,
                col_left = 0, col_right = col_size - 1;
        vector<int> ret(total_size);
        int m, cnt = 0;
        for (; cnt < total_size;) {
            //最上面的第一行
            for (m = col_left; m <= col_right && cnt < total_size; ++m, ++cnt)
                ret[cnt] = matrix[row_left][m];
            ++row_left;
            //最后一列
            for (m = row_left; m <= row_right && cnt < total_size; ++m, ++cnt)
                ret[cnt] = matrix[m][col_right];
            --col_right;
            //最后一行
            for (m = col_right; m >= col_left && cnt < total_size; --m, ++cnt)
                ret[cnt] = matrix[row_right][m];
            --row_right;
            //第一列
            for (m = row_right; m >= row_left && cnt < total_size; --m, ++cnt)
                ret[cnt] = matrix[m][col_left];
            ++col_left;
        }
        return ret;
    }
};

// int main() {
//     vector<vector<int> > matrixs{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
//     Solution sl;
//     const auto &order = sl.spiralOrder(matrixs);
//     for_each(order.begin(), order.end(), [](int x) { cout << x << " "; });
//     return 0;
// }
