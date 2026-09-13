/**
 * 70. 爬楼梯
已解答
简单
相关标签
premium lock icon
相关企业
提示
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

 

示例 1：

输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：

输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
 

提示：

1 <= n <= 45
 */
//二维矩阵计算斐波那契数列
#include <vector>
#include <iostream>
using namespace std;

class Solution {
    vector<vector<int>> matrix
    {
        {1,1},
        {1,0}
    };

    void mul_matrix(vector<vector<int>>& r1,vector<vector<int>>& r2){
        vector<vector<int>> ret(2,vector<int>{0,0});
        ret[0][0] = r1[0][0] * r2[0][0] + r1[0][1] * r2[1][0];
        ret[0][1] = r1[0][0] * r2[0][1] + r1[0][1] * r2[1][1];
        ret[1][0] = r1[1][0] * r2[0][0] + r1[1][1] * r2[1][0];
        ret[1][1] = r1[1][0] * r2[0][1] + r1[1][1] * r2[1][1];
        r1.swap(ret);
    } 

    //幂乘运算求矩阵乘积
    void calculate_matrix(vector<vector<int>>& ret,int time){
        //如果指数是奇数，幂乘运算分成 (time - 1) /2 的平方 +1次
        if(time == 1)
            ret = matrix;
        else if(time % 2){
            calculate_matrix(ret,(time-1)/2);
            mul_matrix(ret,ret);
            mul_matrix(ret,matrix);
        }else{
            calculate_matrix(ret,time / 2);
            mul_matrix(ret,ret);
        }
    }

public:
    int climbStairs(int n) {
        //小于等于2，直接返回
        //超过2，需要计算矩阵的n次方
        vector<vector<int>> ret;
        calculate_matrix(ret,n);
        return ret[0][0];
    }
};

// int main(){
//     int n = 1;
//     Solution sl;
//     cout << sl.climbStairs(n) << endl;
//     return 0;
// }