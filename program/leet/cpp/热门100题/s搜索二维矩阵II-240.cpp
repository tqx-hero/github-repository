//
// Created by 田庆新 on 2026/9/2.
//
/**
* 240. 搜索二维矩阵 II
中等
相关标签
premium lock icon
相关企业
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。


示例 1：


输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
输出：true
示例 2：


输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false


提示：

m == matrix.length
n == matrix[i].length
1 <= n, m <= 300
-109 <= matrix[i][j] <= 109
每行的所有元素从左到右升序排列
每列的所有元素从上到下升序排列
-109 <= target <= 109
 * @return
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int> > &matrix, int target) {
        int row_size = static_cast<int>(matrix.size()), col_size = static_cast<int>(matrix[0].size());
        int row_index = 0, col_index = col_size - 1;
        for (; row_index < row_size && col_index >= 0;) {
            int value = matrix[row_index][col_index];
            if (value == target)
                return true;
            //如果左上角元素值大于目标元素，那么这整列必定大于target，直接减去一列
            if (value > target)
                --col_index;
            else
                //如果小于target，那么整行都小于target，直接减去一行
                ++row_index;
        }
        return false;
    }
};

// int main() {
//     vector<vector<int> > matrix = {
//         {1, 4, 7, 11, 15},
//         {2, 5, 8, 12, 19}, {3, 6, 9, 16, 22}, {10, 13, 14, 17, 24}, {18, 21, 23, 26, 30}
//     };
//     int target = 20;
//     Solution sl;
//     cout << sl.searchMatrix(matrix, target) << endl;
//     return 0;
// }
