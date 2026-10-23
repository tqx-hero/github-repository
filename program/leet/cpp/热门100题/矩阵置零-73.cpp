//
// Created by 田庆新 on 2026/9/1.
//
/**
* 73. 矩阵置零
中等
相关标签
premium lock icon
相关企业
提示
给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。



示例 1：


输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]
示例 2：


输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]


提示：

m == matrix.length
n == matrix[0].length
1 <= m, n <= 200
-231 <= matrix[i][j] <= 231 - 1
 * @return
 */
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int> > &matrix) {
        //用两个哈希表存储需要修改的行与列
        unordered_set<int> col_set, row_set;
        int i = 0, j = 0, row_size = static_cast<int>(matrix.size()), col_size = static_cast<int>(matrix[0].size());
        for (; i < row_size; ++i) {
            for (j = 0; j < col_size; ++j) {
                if (!matrix[i][j]) {
                    row_set.emplace(i);
                    col_set.emplace(j);
                }
            }
        }
        for (i = 0; i < row_size; ++i) {
            for (j = 0; j < col_size; ++j) {
                if (row_set.count(i) || col_set.count(j))
                    matrix[i][j] = 0;
            }
        }
    }
};

// int main() {
//     vector<vector<int> > matrix{{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
//     Solution sl;
//     sl.setZeroes(matrix);
//     for_each(matrix.begin(), matrix.end(), [](const vector<int> &vc) {
//         for_each(vc.begin(), vc.end(), [](const int &x) { cout << x << " "; });
//         cout << endl;
//     });
//     return 0;
// }
