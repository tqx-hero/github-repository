//
// Created by Administrator on 2026/8/10.
//
/**
* 旋转图像
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。 
 * @return
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int> > &matrix) {
        int ma_size = static_cast<int>(matrix.size());
        if (ma_size == 1)
            return;
        //先以行为单位翻转
        for (int left = 0, right = ma_size - 1; left < right; left++, right--)
            swap(matrix[left], matrix[right]);
        //在以对角线为轴进行值替换
        for (int i = 0; i < ma_size; i++)
            for (int j = 0; j < i; j++)
                swap(matrix[i][j], matrix[j][i]);
    }
};

// int main() {
//     vector<vector<int> > matrix{{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
//     Solution sl;
//     sl.rotate(matrix);
//     for_each(matrix.begin(), matrix.end(), [](const vector<int> &vc) {
//         for_each(vc.begin(), vc.end(), [](const int x) {
//             cout << x << "\t";
//         });
//         cout << endl;
//     });
//     return 0;
// }
