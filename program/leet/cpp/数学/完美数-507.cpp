/**
 *507. 完美数
简单
相关标签
premium lock icon
相关企业
对于一个 正整数，如果它和除了它自身以外的所有 正因子 之和相等，我们称它为 「完美数」。

给定一个 整数 n， 如果是完美数，返回 true；否则返回 false。

 

示例 1：

输入：num = 28
输出：true
解释：28 = 1 + 2 + 4 + 7 + 14
1, 2, 4, 7, 和 14 是 28 的所有正因子。
示例 2：

输入：num = 7
输出：false
 

提示：

1 <= num <= 108
 */
#include <iostream>
#include <cmath>
using namespace std;

class Solution {
public:
    bool checkPerfectNumber(int num) {
	   int max_bound = static_cast<int>(ceil(sqrt(num)));
	   int sum = 1,i;
	   for(i = 2;i < max_bound;++i){
	   	if(num % i == 0){
			sum += i;
			sum += num / i;
		}
	   }
	   if(max_bound * max_bound == num)
		   sum += max_bound;
	   return sum == num;
    }
};

int main(){
	int num = 6;
	Solution sl;
	cout << sl.checkPerfectNumber(num) << endl;
	return 0;
}
