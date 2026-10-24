#include <string>
/**
 *2409. 统计共同度过的日子数
简单
相关标签
premium lock icon
相关企业
提示
Alice 和 Bob 计划分别去罗马开会。

给你四个字符串 arriveAlice ，leaveAlice ，arriveBob 和 leaveBob 。Alice 会在日期 arriveAlice 到 leaveAlice 之间在城市里（日期为闭区间），而 Bob 在日期 arriveBob 到 leaveBob 之间在城市里（日期为闭区间）。每个字符串都包含 5 个字符，格式为 "MM-DD" ，对应着一个日期的月和日。

请你返回 Alice和 Bob 同时在罗马的天数。

你可以假设所有日期都在 同一个 自然年，而且 不是 闰年。每个月份的天数分别为：[31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31] 。

 

示例 1：

输入：arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
输出：3
解释：Alice 从 8 月 15 号到 8 月 18 号在罗马。Bob 从 8 月 16 号到 8 月 19 号在罗马，他们同时在罗马的日期为 8 月 16、17 和 18 号。所以答案为 3 。
示例 2：

输入：arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01", leaveBob = "12-31"
输出：0
解释：Alice 和 Bob 没有同时在罗马的日子，所以我们返回 0 。
 

提示：

所有日期的格式均为 "MM-DD" 。
Alice 和 Bob 的到达日期都 早于或等于 他们的离开日期。
题目测试用例所给出的日期均为 非闰年 的有效日期。
 */
#include <array>
#include <iostream>
using namespace std;

class Solution {
	int parse_str(string& str){
		int ret = 0,i;
		for(i = 0;i < 5;++i){
			if(i == 2)
				continue;
			ret = ret * 10 + str[i] - '0';
		}
		return ret;
	}
public:
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
	array<int,12> hash_map{
		31,28,31,30,
		31,30,31,31,
		30,31,30,31
	};
	int begin_alice = parse_str(arriveAlice);
	int end_alice = parse_str(leaveAlice);
	int begin_bob = parse_str(arriveBob);
	int end_bob = parse_str(leaveBob);
	//如果两者没交集，返回0
	if(begin_alice > end_bob || end_alice < begin_bob || begin_bob > end_alice || end_bob < begin_alice)
		return 0;
	//有交集，begin取两者较大值，end取两者较小值
	int ret_begin = max(begin_alice , begin_bob),ret_end = min(end_alice , end_bob)
		,begin_month = ret_begin /100,end_month = ret_end / 100;
	//如果是同一个月，直接相减+1
	if(begin_month == end_month)
		return ret_end - ret_begin +1;
	//不是同一个月，先计算两头，再计算中间
	int ret = hash_map[begin_month - 1] - (ret_begin % 100) + 1 + (ret_end % 100);
	//添加中间月份
	int i;
	for(i = begin_month+1; i < end_month;++i)
		ret += hash_map[i -1];
	return ret;
    }
};

int main(){
	//string arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19";
	string arriveAlice = "09-01", leaveAlice = "10-19", arriveBob = "06-19", leaveBob = "10-20";
	Solution sl;
	cout << sl.countDaysTogether(arriveAlice,leaveAlice,arriveBob,leaveBob) << endl;
	return 0;
}
