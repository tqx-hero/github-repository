/**
 * 198. 打家劫舍
已解答
中等
相关标签
premium lock icon
相关企业
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

 

示例 1：

输入：[1,2,3,1]
输出：4
解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：

输入：[2,7,9,3,1]
输出：12
解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋 (金额 = 1)。
     偷窃到的最高金额 = 2 + 9 + 1 = 12 。
 

提示：

1 <= nums.length <= 100
0 <= nums[i] <= 400
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//每个房子都有两个状态：被打劫、没有被打劫
//用动态规划，使用一个二维数组dp[size][2]
//size为原数组的大小
//dp数组表示为每个房屋的两种状态下
//得到的钱累计总数
class Solution {
public:
    int rob(vector<int>& nums) {
        int size = static_cast<int>(nums.size());
        //记录每间房子的每个状态下的累计获得钱数
        //0下标代表本房间不打劫，1下标代表打劫
        vector<vector<int>> dp(size,vector<int>(2,0));
        dp[0][0] = 0;
        dp[0][1] = nums[0];
        //从第二个开始遍历
        int i;
        //状态转移方程：
        //f(x) = max{f(x-1)[1],f(x-1)[0]+nums[x]}
        //f(0)[0] = 0;f(0)[1] =nums[0];
        for(i=1;i<size;++i){
            dp[i][0] = max(dp[i-1][1],dp[i-1][0]);
            dp[i][1] = dp[i-1][0]+nums[i];
        }
        return max(dp[size-1][0],dp[size-1][1]);
    }
};

// int main(){
//     // vector<int> nums{1,2,3,1};
//     vector<int> nums{2,7,9,3,1};
//     // vector<int> nums{2,1,1,2};
//     Solution sl;
//     cout << sl.rob(nums) << endl;
//     return 0;
// }