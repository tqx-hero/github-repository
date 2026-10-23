/*
74. 搜索二维矩阵
中等
相关标签
premium lock icon
相关企业
给你一个满足下述两条属性的 m x n 整数矩阵：

每行中的整数从左到右按非严格递增顺序排列。
每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。

你必须编写一个时间复杂度为 O(log(m * n)) 的解决方案。

 

示例 1：


输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true
示例 2：


输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 100
-104 <= matrix[i][j], target <= 104
*/
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int row_size = static_cast<int>(matrix.size()),col_size = static_cast<int>(matrix[0].size());
        //先以行为单位进行二分查找
        int j = col_size -1,row_left = 0,row_right = row_size-1;
        for(;row_left < row_right && matrix[row_left][j] < target;){
            int mid = row_left +(row_right - row_left) /2;
            int val = matrix[mid][j];
            if (val == target)
                return true;
            if(val < target)
                row_left = mid + 1;
            else
                row_right =mid;
        }
        //如果row_left没有越界，则row_left行为可能存在target数，二分查找改行
        if(row_left >= row_size)
            return false;
        int col_left =0,col_right = col_size -1;
        for(;col_left <= col_right;){
            int mid = col_left + (col_right -col_left) /2;
            int val = matrix[row_left][mid];
            if(val == target)
                return true;
            if(val > target)
                col_right = mid - 1;
            else 
                col_left = mid + 1;
        }
        return false;
    }
};

// int main(){
//     //matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
//     // vector<vector<int>> matrix{
//     //     {1,3,5,7},
//     //     {10,11,16,20},
//     //     {23,30,34,60}
//     // };
//     // int target = 3;
//     //matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
//     vector<vector<int>> matrix{
//         {1,3,5,7},
//         {10,11,16,20},
//         {23,30,34,60}
//     };
//     int target = 13;
//     Solution sl;
//     cout << sl.searchMatrix(matrix,target) << endl;
//     return 0;
// }