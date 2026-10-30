/**
728. 自除数
简单
相关标签
premium lock icon
相关企业
提示
自除数 是指可以被它包含的每一位数整除的数。

例如，128 是一个 自除数 ，因为 128 % 1 == 0，128 % 2 == 0，128 % 8 == 0。
自除数 不允许包含 0 。

给定两个整数 left 和 right ，返回一个列表，列表的元素是范围 [left, right]（包括两个端点）内所有的 自除数 。

 

示例 1：

输入：left = 1, right = 22
输出：[1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22]
示例 2:

输入：left = 47, right = 85
输出：[48,55,66,77]
 

提示：

1 <= left <= right <= 104
  */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
    bool is_valid(int n){
	int tmpn = n;
	while(tmpn){
	    int remain = tmpn % 10;
	    if(!remain || n % remain)
		return false;
	    tmpn /= 10;
	}
	return true;
    }
public:
    vector<int> selfDividingNumbers(int left, int right) {
	vector<int> ret;
	int i;
	for(i=left;i <= right;++i){
	    if(is_valid(i))
		ret.push_back(i);
	}
	return ret;
    }
};

int main(){
    int left = 1,right = 22;
    Solution sl;
    const auto& vc = sl.selfDividingNumbers(left,right);
    for_each(vc.begin(),vc.end(),[](const int x){cout << x <<  " ";});
    cout << endl;
    return 0;
}
