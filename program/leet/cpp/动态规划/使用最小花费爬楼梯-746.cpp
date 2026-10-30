/**
746. 使用最小花费爬楼梯
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i 个台阶向上爬需要支付的费用。

一旦你支付此费用，即可选择向上爬 一个 或者 两个 台阶。

你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。

请你计算并返回达到楼梯顶部的 最低 花费，即最后一步之后的那个位置（下标 cost.length）。

 

示例 1：

输入：cost = [10,15,20]
输出：15
解释：你将从下标为 1 的台阶开始。
- 支付 15 ，向上爬两个台阶，到达楼梯顶部。
总花费为 15 。
示例 2：

输入：cost = [1,100,1,1,1,100,1,1,100,1]
输出：6
解释：你将从下标为 0 的台阶开始。
- 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
- 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
- 支付 1 ，向上爬一个台阶，到达楼梯顶部。
总花费为 6 。
 

提示：

2 <= cost.length <= 1000
0 <= cost[i] <= 999
  */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    /*
    int minCostClimbingStairs(vector<int>& cost) {
	size_t sz = cost.size();
	vector<vector<int>> dp(sz,vector<int>(2));
	dp[0][0] = 0; //设置第一位的值，0号位代表不经过该点的最小费用，1号位代表经过该点时的最小费用
	dp[0][1] = cost[0]; 
	int i;
	for(i=1;i < sz;++i){
	    dp[i][0] = dp[i-1][1];//不经过该点时，那必然经过i-1点，因为最大步长是2
	    dp[i][1] = std::min(dp[i-1][0],dp[i-1][1]) + cost[i]; //经过该点时，取前一个顶点的较小值+当前顶点的值
	}
	return std::min(dp[sz - 1][0],dp[sz - 1][1]);
    }
    */
    int minCostClimbingStairs(vector<int>& cost) {
	size_t sz = cost.size();
	int no_cross = 0,cross = cost[0];
	int i;
	for(i=1;i < sz;++i){
	    int temp = no_cross;
	    no_cross = cross;//不经过该点时，那必然经过i-1点，因为最大步长是2
	    cross = std::min(temp,cross) + cost[i];
	}
	return std::min(no_cross,cross);
    }
};

int main(){
    //cost = [10,15,20]
//    vector<int> cost{10,15,20};
    vector<int> cost{1,100,1,1,1,100,1,1,100,1};
    Solution sl;
    cout << sl.minCostClimbingStairs(cost) << endl;
    return 0;
}
