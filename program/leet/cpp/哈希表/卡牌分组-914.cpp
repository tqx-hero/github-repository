/**
914. 卡牌分组
简单
相关标签
premium lock icon
相关企业
给定一副牌，每张牌上都写着一个整数。

此时，你需要选定一个数字 X，使我们可以将整副牌按下述规则分成 1 组或更多组：

每组都有 X 张牌。
组内所有的牌上都写着相同的整数。
仅当你可选的 X >= 2 时返回 true。

 

示例 1：

输入：deck = [1,2,3,4,4,3,2,1]
输出：true
解释：可行的分组是 [1,1]，[2,2]，[3,3]，[4,4]
示例 2：

输入：deck = [1,1,1,2,2,2,3,3]
输出：false
解释：没有满足要求的分组。

提示：

1 <= deck.length <= 104
0 <= deck[i] < 104
  */
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

//统计数字出现次数，再求次数的最大公约数是否大于1
class Solution {
	int get_max_val(int x1,int x2){
		int bigger,small;
		bigger = std::max(x1,x2);
		small = std::min(x1,x2);
		while(small){
			int temp = bigger % small;
			bigger = small;
			small = temp;
		}
		return bigger;
	}
public:
    bool hasGroupsSizeX(vector<int>& deck) {
	    unordered_map<int,int> map;
	    size_t sz = deck.size();
	    int i,max_dived;
	    for(i = 0;i < sz;++i)
		    map[deck[i]]++;
	    max_dived = map[deck[0]];
	    //遍历词频，找到最大公约数，如果最大公约数为1，返回false，否则true
	    for(auto& pair : map){
		    //计算两个值最大公约数
		    if((max_dived = get_max_val(max_dived,pair.second)) == 1)
			    return false;
	    }
	    return true;
    }
};

int main(){
	vector<int> deck{1,2,3,4,4,3,2,1};
	Solution sl;
	cout << sl.hasGroupsSizeX(deck) << endl;
	return 0;
}
