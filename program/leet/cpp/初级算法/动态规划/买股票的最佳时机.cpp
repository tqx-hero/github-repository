//
// Created by Administrator on 2026/8/14.
//
/**
* 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。 
示例 1：
输入：
[7,1,5,3,6,4]
输出：
5
解释：
在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 = 6）的时候卖出，最大利润 = 6-1 = 5 。
     注意利润不能是 7-1 = 6, 因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：
输入：
prices = [7,6,4,3,1]
输出：
0
解释：
在这种情况下, 没有交易完成, 所以最大利润为 0。
  提示：
• 1 <= prices.length <= 105
• 0 <= prices[i] <= 104
 * @return
 */
#include <iostream>
#include <stack>
#include <vector>
using namespace std;

class Solution {
public:
    //用单调栈解决
    // int maxProfit(vector<int> &prices) {
    //     deque<int> stk;
    //     int total = 0;
    //     for (auto price: prices) {
    //         if (stk.empty())
    //             stk.push_front(price);
    //         else {
    //             //等于栈顶，丢弃
    //             int top_price = stk.front();
    //             if (top_price == price)
    //                 continue;
    //             //比栈顶大，入栈
    //             if (top_price < price) {
    //                 stk.push_front(price);
    //             } else {
    //                 //比栈顶小，先统计栈内元素的最大差值(因为是单调栈，只需要头-尾即可得出),大于total则替换结果。
    //                 int back_price = stk.back();
    //                 total = std::max(total, top_price - back_price);
    //                 //替换后比较当前元素与栈底最小值哪个大，大于等于则丢弃，小于则清空栈，将当前元素入栈
    //                 if (price < back_price) {
    //                     stk.clear();
    //                     stk.push_front(price);
    //                 }
    //             }
    //         }
    //     }
    //     return std::max(total, stk.front() - stk.back());
    // }

    int maxProfit(vector<int> &prices) {
        size_t size = prices.size();
        vector<vector<int> > dp;
        dp.resize(size);
        //二维数组来统计每天在持有股票与不持有股票的两种情况的利润
        //0号位置表示不持有股票
        //1号位置表示持有股票
        dp[0] = {0, -prices[0]};
        for (int i = 1; i < size; i++) {
            dp[i] = {
                //今天不持有股票有2种情况：
                //1、i-1天时不持有股票，此时利润为前一天的利润
                //2、i-1天持有股票，利润即为卖出股票的利润。由于买股票的利润用负数表示，所以可以直接用利润相加
                //3、两者取最大值
                max(dp[i - 1][0], dp[i - 1][1] + prices[i]),
                //今天持有股票，同样有两种情况：
                //1、昨天不持有股票，说明今天刚入手，利润为-princes[i];
                //2、昨天同样持有股票。今天仍然持有，说明今天不会卖掉，利润继承前者即可
                //3、两者取最大值
                max(dp[i - 1][1], -prices[i])
            };
        }
        return dp[size - 1][0];
    }
};

// int main() {
//     vector<int> prices{2, 1, 2, 1, 0, 1, 2};
//     // vector<int> prices{7,6,5,4,3,2,1};
//     // vector<int> prices{7, 1, 5, 3, 6, 4};
//     Solution sl;
//     cout << sl.maxProfit(prices) << endl;
//     return 0;
// }
