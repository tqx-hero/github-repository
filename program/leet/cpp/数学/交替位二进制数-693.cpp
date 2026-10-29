/**
 *693. 交替位二进制数
简单
相关标签
premium lock icon
相关企业
给定一个正整数，检查它的二进制表示是否总是 0、1 交替出现：换句话说，就是二进制表示中相邻两位的数字永不相同。

 

示例 1：

输入：n = 5
输出：true
解释：5 的二进制表示是：101
示例 2：

输入：n = 7
输出：false
解释：7 的二进制表示是：111.
示例 3：

输入：n = 11
输出：false
解释：11 的二进制表示是：1011.
 

提示：

1 <= n <= 231 - 1
 */
#include <iostream>
using namespace std;

class Solution {
public:
    bool hasAlternatingBits(int n) {
	    int now_num = n & 0x1;
	    //当n不等于0时，需要查看末尾值
	    while(n >>= 1){
		    if((n & 0x1) == now_num)
			    return false;
		    now_num ^= 1;
	    }
	    return true;
    }
};

int main(){
	int n =8;
	Solution sl;
	cout << sl.hasAlternatingBits(n) << endl;
	return 0;
}
