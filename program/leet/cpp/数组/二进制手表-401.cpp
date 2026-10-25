/**
 *401. 二进制手表
简单
相关标签
premium lock icon
相关企业
提示
二进制手表顶部有 4 个 LED 代表 小时（0-11），底部的 6 个 LED 代表 分钟（0-59）。每个 LED 代表一个 0 或 1，最低位在右侧。

例如，下面的二进制手表读取 "4:51" 。


给你一个整数 turnedOn ，表示当前亮着的 LED 的数量，返回二进制手表可以表示的所有可能时间。你可以 按任意顺序 返回答案。

小时不会以零开头：

例如，"01:00" 是无效的时间，正确的写法应该是 "1:00" 。
分钟必须由两位数组成，可能会以零开头：

例如，"10:2" 是无效的时间，正确的写法应该是 "10:02" 。
 

示例 1：

输入：turnedOn = 1
输出：["0:01","0:02","0:04","0:08","0:16","0:32","1:00","2:00","4:00","8:00"]
示例 2：

输入：turnedOn = 9
输出：[]
 

提示：

0 <= turnedOn <= 10
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
using namespace std;
//小时每位取值为8,4,2,1
//分钟每位取值为32,16,8,4,2,1

//小时可亮灯最多有三个
//0个灯，取值是：0
//1个灯时，可亮随意1个，取值是：1，2，4，8
//2个灯，除了8，4不能同时亮，其余两两组合都可，取值：3，5，6，9，10
//3个灯，取值是：7，11

//分钟可亮灯的个数与取值：
//0个灯，取值为：0
//1个灯：取值：1，2，4，8，16，32
//2个灯：取值：3，5，9，17，33，6，10，18，34，12，20，36，24，40，48
//3个灯，取值：7，11，19，35，13，21，37，25，41，49，14，22，38，26，42，50，
//4个灯，
//5个灯
class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
	vector<string> ret;
	if(turnedOn > 8)
		return ret;
	//枚举小时与分钟取值，key为灯亮的个数
	array<vector<string>,4> hour{
		vector{string{"0"}},
		vector{string{"1"},string{"2"},string{"4"},string{"8"}},
		vector{string{"3"},string{"5"},string{"6"},string{"9"},string{"10"}},
		vector{string{"7"},string{"11"}}
	};
	array<vector<string>,6> minutes{
		vector{string{"00"}},
		vector{string{"01"},string{"02"},string{"04"},string{"08"},string{"16"},string{"32"}},//1个灯
		vector{string{"03"},string{"05"},string{"06"},string{"09"},string{"10"},string{"12"},string{"17"},
			string{"18"},string{"20"},string{"24"},string{"33"},string{"34"},string{"36"},string{"40"},string{"48"}},    //2
		vector{string{"07"},string{"11"},string{"13"},string{"14"},string{"19"},string{"21"},string{"22"},string{"25"}
			,string{"26"},string{"28"},string{"35"},string{"37"},string{"38"},string{"41"},string{"42"},string{"44"},string{"49"},
				string{"50"},string{"52"},string{"56"}},    //3
		vector{string{"15"},string{"23"},string{"27"},string{"29"},string{"30"},string{"39"},string{"43"},string{"45"},string{"46"},
			string{"51"},string{"53"},string{"54"},string{"57"},string{"58"}},    //4
		vector{string{"31"},string{"47"},string{"55"},string{"59"}}     //5
	};
	int i,j,max_index = min(3,turnedOn);
	for(i=0;i <= max_index;++i){
		//分钟需要亮的灯个数
		j = turnedOn -i;
		if(j < 6){
			auto& hour_vc = hour[i];
			auto& minutes_vc = minutes[j];
			for(auto &str : hour_vc){
				
				for(auto &str_m : minutes_vc){
					ret.push_back(str+":"+str_m);
				}
			}
		}
	}
	return ret;
    }
};

int main(){
	int turnedOn = 1;
	Solution sl;
	const auto& vc = sl.readBinaryWatch(turnedOn);
	for_each(vc.begin(),vc.end(),[](const string& str){cout << str << " ";});
	cout << endl;
	return 0;
}
