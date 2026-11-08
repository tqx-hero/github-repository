/**
1013. 将数组分成和相等的三个部分
简单
相关标签
premium lock icon
相关企业
提示
给你一个整数数组 arr，只有可以将其划分为三个和相等的 非空 部分时才返回 true，否则返回 false。

形式上，如果可以找出索引 i + 1 < j 且满足 (arr[0] + arr[1] + ... + arr[i] == arr[i + 1] + arr[i + 2] + ... + arr[j - 1] == arr[j] + arr[j + 1] + ... + arr[arr.length - 1]) 就可以将数组三等分。

 

示例 1：

输入：arr = [0,2,1,-6,6,-7,9,1,2,0,1]
输出：true
解释：0 + 2 + 1 = -6 + 6 - 7 + 9 + 1 = 2 + 0 + 1
示例 2：

输入：arr = [0,2,1,-6,6,7,9,-1,2,0,1]
输出：false
示例 3：

输入：arr = [3,3,6,5,-2,2,5,1,-9,4]
输出：true
解释：3 + 3 = 6 = 5 - 2 + 2 + 5 + 1 - 9 + 4
 

提示：

3 <= arr.length <= 5 * 104
-104 <= arr[i] <= 104
  */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool canThreePartsEqualSum(vector<int>& arr) {
	    unordered_map<int,int> cache;
	    size_t sz = arr.size();
	    vector<int> prefix(sz + 1);
	    int i;
	    prefix[0] = 0;
	    for(i = 1;i < sz;++i)
		    prefix[i] = prefix[i - 1] + arr[i - 1];
	    prefix[i] = prefix[i - 1] + arr[i - 1];
	    //将以值为key，出现个数为value放入哈希表
	    for(i = 1;i < sz;++i)
		    cache[prefix[i]]++;
	    //再次遍历前缀和数组，找是否有符合要求的值
	    int lastone = prefix[sz];
	    for(i = 1;i < sz;++i){
		    int curnum = prefix[i];
		    if(--cache[curnum] == 0)
			    cache.erase(curnum);
		    if(curnum * 3 == lastone && cache.count(curnum * 2))
			    return true;
	    }
	    return false;
    }
};

int main(){
//	vector<int> arr{0,2,1,-6,6,-7,9,1,2,0,1};
//	vector<int> arr{3,3,6,5,-2,2,5,1,-9,4};
	vector<int> arr{1,-1,1,-1};
	Solution sl;
	cout << sl.canThreePartsEqualSum(arr) << endl;
	return 0;
}
