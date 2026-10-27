/**
 *605. 种花问题
简单
相关标签
premium lock icon
相关企业
假设有一个很长的花坛，一部分地块种植了花，另一部分却没有。可是，花不能种植在相邻的地块上，它们会争夺水源，两者都会死去。

给你一个整数数组 flowerbed 表示花坛，由若干 0 和 1 组成，其中 0 表示没种植花，1 表示种植了花。另有一个数 n ，能否在不打破种植规则的情况下种入 n 朵花？能则返回 true ，不能则返回 false 。

 

示例 1：

输入：flowerbed = [1,0,0,0,1], n = 1
输出：true
示例 2：

输入：flowerbed = [1,0,0,0,1], n = 2
输出：false
 

提示：

1 <= flowerbed.length <= 2 * 104
flowerbed[i] 为 0 或 1
flowerbed 中不存在相邻的两朵花
0 <= n <= flowerbed.length
 */
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Solution {

	void add_cnt(int left,int right,int &cnt){
		for(left +=2;left < right;left += 2){
			if(left + 1 < right)
				++cnt;
		}
	}
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
	    int left;
	    left = (flowerbed[0] == 1 ? 0 : -2);
	    size_t size = flowerbed.size();
	    int i,cnt = 0;
	    for(i=1;i<size;++i){
		    if(flowerbed[i] == 0)
			    continue;
		    //如果i位置为1，需要看前面的1到这个1之间可以填充几个1
		    add_cnt(left,i,cnt);
		    if(cnt >= n)
			    return true;
		    left = i;
	    }
	    //记录最后一次left~size-1可填充几个1
	    if(flowerbed[size - 1] == 0)
		    add_cnt(left,size + 1,cnt);
	    else
		    add_cnt(left,size -1,cnt);
	    return cnt >= n;
    }
};

int main(){
//	flowerbed = [1,0,0,0,1], n = 1
//	vector<int> flowerbed{1,0,0,0,1};
	vector<int> flowerbed{0,0,1,0,1};
	int n =1;
//	int n =2;
	Solution sl;
	cout << sl.canPlaceFlowers(flowerbed,n) << endl;
	return 0;
}
