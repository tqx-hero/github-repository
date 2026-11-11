/**
  3789. 采购的最小花费
  中等
  相关标签
  premium lock icon
  相关企业
  提示
  给你五个整数 cost1, cost2, costBoth, need1 和 need2。

  有三种类型的物品可以购买：

  类型 1 的物品花费 cost1，并仅满足类型 1 的需求 1 个单位。
  类型 2 的物品花费 cost2，并仅满足类型 2 的需求 1 个单位。
  类型 3 的物品花费 costBoth，同时满足类型 1 和类型 2 的需求各 1 个单位。
  你需要购买足够的物品，使得：

  满足类型 1 的总需求 至少 为 need1。
  满足类型 2 的总需求 至少 为 need2。
  返回满足这些需求的 最小 可能总花费。



  示例 1：

  输入： cost1 = 3, cost2 = 2, costBoth = 1, need1 = 3, need2 = 2

  输出： 3

  解释：

  购买 3 个类型 3 的物品，总花费为 3 * 1 = 3，此时类型 1 的总需求满足 3（>= need1 = 3），类型 2 的总需求满足 3（>= need2 = 2）。
  任何其他有效的购买方案都会花费更多，因此最小总花费为 3。

  示例 2：

  输入： cost1 = 5, cost2 = 4, costBoth = 15, need1 = 2, need2 = 3

  输出： 22

  解释：

  购买 need1 = 2 个类型 1 的物品和 need2 = 3 个类型 2 的物品，总花费为 2 * 5 + 3 * 4 = 10 + 12 = 22。
  任何其他有效的购买方案都会花费更多，因此最小总花费为 22。

  示例 3：

  输入： cost1 = 5, cost2 = 4, costBoth = 15, need1 = 0, need2 = 0

  输出： 0

  解释：

  由于不需要任何物品（need1 = need2 = 0），因此无需购买，总花费为 0。



  提示：

  1 <= cost1, cost2, costBoth <= 106
  0 <= need1, need2 <= 109
 */
#include <stdio.h>
#include <stdlib.h>

//贪心算法。
//1、计算need的较小值，再取cost的和与costBoth的较小值，两者相乘，得出相同数量的1，2要花费的最小值
//2、再找到need还没有达到数量的，比如need1还没达到要求，就比较cost1与costBoth哪个小，用较小值与剩余数量相乘
//以上两步骤结果相加
static long long  min(const long long  a,const long long b){
    return a <= b ? a : b;
}

long long minimumCost(int cost1, int cost2, int costBoth, int need1, int need2) {
    long long ret = 0;
    long long need_min = min(need1,need2);
    long long cboth_min = min((long long) (cost1 + cost2),costBoth);
    ret += need_min * cboth_min;
    if(need1 > need_min)
        ret += (need1 - need_min) * min(cost1,costBoth);
    else if(need2 > need_min)
        ret += (need2 - need_min) * min(cost2,costBoth);
    return ret;
}

int main(){
    int cost1 = 3, cost2 = 2, costBoth = 1, need1 = 3, need2 = 2;
    fprintf(stdout,"%lld\n",minimumCost(cost1,cost2,costBoth,need1,need2));
    exit(0);
}
