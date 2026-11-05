/**
1385. 两个数组间的距离值
尝试过
简单
相关标签
premium lock icon
相关企业
提示
给你两个整数数组 arr1 ， arr2 和一个整数 d ，请你返回两个数组之间的 距离值 。

「距离值」 定义为符合此距离要求的元素数目：对于元素 arr1[i] ，不存在任何元素 arr2[j] 满足 |arr1[i]-arr2[j]| <= d 。

 

示例 1：

输入：arr1 = [4,5,8], arr2 = [10,9,1,8], d = 2
输出：2
解释：
对于 arr1[0]=4 我们有：
|4-10|=6 > d=2 
|4-9|=5 > d=2 
|4-1|=3 > d=2 
|4-8|=4 > d=2 
所以 arr1[0]=4 符合距离要求

对于 arr1[1]=5 我们有：
|5-10|=5 > d=2 
|5-9|=4 > d=2 
|5-1|=4 > d=2 
|5-8|=3 > d=2
所以 arr1[1]=5 也符合距离要求

对于 arr1[2]=8 我们有：
|8-10|=2 <= d=2
|8-9|=1 <= d=2
|8-1|=7 > d=2
|8-8|=0 <= d=2
存在距离小于等于 2 的情况，不符合距离要求 

故而只有 arr1[0]=4 和 arr1[1]=5 两个符合距离要求，距离值为 2
示例 2：

输入：arr1 = [1,4,2,3], arr2 = [-4,-3,6,10,20,30], d = 3
输出：2
示例 3：

输入：arr1 = [2,1,100,3], arr2 = [-5,-2,10,-3,7], d = 6
输出：1
 

提示：

1 <= arr1.length, arr2.length <= 500
-10^3 <= arr1[i], arr2[j] <= 10^3
0 <= d <= 100
  */
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;
//把arr2 放到红黑树上
class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
	    int ret = 0;
	    set<int> cache{arr2.begin(),arr2.end()};
	    set<int>::iterator it,end = cache.end(),begin = cache.begin();
	    for(auto& num : arr1){
		    if((it = cache.lower_bound(num)) != end && abs(*it - num) <=  d || (it != begin && abs(*--it - num) <= d)) //找到第一个不小于该值的第一个值
			    continue;
		    ++ret;
	    }
	    return ret; 
    }
};

int main(){
	vector<int> arr1{4,5,8}, arr2{10,9,1,8};
	int d = 2;
	Solution sl;
	cout << sl.findTheDistanceValue(arr1,arr2,d) << endl;
	return 0;
}
