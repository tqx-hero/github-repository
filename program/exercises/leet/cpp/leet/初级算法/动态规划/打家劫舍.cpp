//
// Created by Administrator on 2026/8/15.
//
/**
* 打家劫舍
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



作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/xnq4km/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <vector>
#include <array>
#include <iostream>
using namespace std;

//动态规划+贪心算法
class Solution {
public:
    // int rob(vector<int> &nums) {
    //     //动态规划，每个房屋有2个状态：被偷窃与不被偷窃。
    //     //设定数组，每个元素是一个大小为2的数组，分别表示当前房屋的状态，即被偷窃与没被偷窃。
    //     //分别计算这两种状态情况下已经得到的金币数量，最后取最后一个元素的最大值即可
    //     size_t size = nums.size();
    //     if (size == 1)
    //         return nums[0];
    //     vector<array<int, 2> > dp;
    //     dp.resize(size);
    //     //每个子数组的0号位表示不偷窃当前房屋、1号位表示偷窃当前房屋
    //     dp[0][0] = 0;
    //     dp[0][1] = nums[0];
    //     for (int i = 1; i < size; i++) {
    //         //当前房屋如果不被偷窃，那当前金币应该等于:
    //         //1、上一个房屋被偷情况下的得到金币
    //         //2、上一个房屋没有被偷情况下得到的金币
    //         //3、上述2步骤取最大值
    //         dp[i][0] = max(dp[i - 1][1], dp[i - 1][0]);
    //         //当前房屋如果被偷，那当前金币应该等于上个房屋没被偷+当前房屋的金币
    //         dp[i][1] = dp[i - 1][0] + nums[i];
    //     }
    //     return max(dp[size - 1][0], dp[size - 1][1]);
    // }
    //不用二维数组，直接用两个值代表当前房屋被偷时与不被偷时各自获得的总金币，到最后取两者最大即可
    int rob(vector<int> &nums) {
        size_t size = nums.size();
        int no_robed = 0, robed = nums[0];
        for (int i = 1; i < size; i++) {
            int temp_no_robed = no_robed;
            no_robed = max(temp_no_robed, robed);
            robed = temp_no_robed + nums[i];
        }
        return max(no_robed, robed);
    }
};

// int main() {
//     vector<int> nums{1, 2, 3, 1};
//     // vector<int> nums{2, 7, 9, 3, 1};
//     Solution sl;
//     cout << sl.rob(nums) << endl;
//     return 0;
// }
