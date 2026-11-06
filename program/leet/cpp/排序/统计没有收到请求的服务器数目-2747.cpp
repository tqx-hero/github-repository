/**
2747. 统计没有收到请求的服务器数目
中等
相关标签
premium lock icon
相关企业
提示
给你一个整数 n ，表示服务器的总数目，再给你一个下标从 0 开始的 二维 整数数组 logs ，其中 logs[i] = [server_id, time] 表示 id 为 server_id 的服务器在 time 时收到了一个请求。

同时给你一个整数 x 和一个下标从 0 开始的整数数组 queries  。

请你返回一个长度等于 queries.length 的数组 arr ，其中 arr[i] 表示在时间区间 [queries[i] - x, queries[i]] 内没有收到请求的服务器数目。

注意时间区间是个闭区间。

 

示例 1：

输入：n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
输出：[1,2]
解释：
对于 queries[0]：id 为 1 和 2 的服务器在区间 [5, 10] 内收到了请求，所以只有服务器 3 没有收到请求。
对于 queries[1]：id 为 2 的服务器在区间 [6,11] 内收到了请求，所以 id 为 1 和 3 的服务器在这个时间段内没有收到请求。
示例 2：

输入：n = 3, logs = [[2,4],[2,1],[1,2],[3,1]], x = 2, queries = [3,4]
输出：[0,1]
解释：
对于 queries[0]：区间 [1, 3] 内所有服务器都收到了请求。
对于 queries[1]：只有 id 为 3 的服务器在区间 [2,4] 内没有收到请求。
 

提示：

1 <= n <= 105
1 <= logs.length <= 105
1 <= queries.length <= 105
logs[i].length == 2
1 <= logs[i][0] <= n
1 <= logs[i][1] <= 106
1 <= x <= 105
x < queries[i] <= 106
  */
#include <vector>
#include <algorithm>
#include <iostream>
#if 0
需要使用滑动窗口，硬遍历的复杂度太高，会超时
using namespace std;
//1、按照时间统计每个时间点访问的服务器集合
//2、对时间数组进行排序
//3、遍历查找时间的数组，根据[left,right]区间找到对应的时间点，比较这个时间段之外的每个时间点的服务器数量，取最大值
class Solution {
	    vector<vector<int>> servers(n);
	
	    int calculate_number(const int left_time,const int last_time){
		    int ret = 0;
		    for(){
		    }
	    }

public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
	    size_t qsz = queries.size();
	    vector<int> ret(qsz);
	    //按照服务器统计每个服务器的访问时间
	    for(const auto& vc : logs)
		    servers[vc[0]].push_back(vc[1]);
	    //对每个服务器的访问数组进行排序
	    for(auto& vc : servers)
		    std::sort(vc.begin(),vc.end());
	    //查询区间，对每个区间搜索每个服务器的有效数量
	    for(const auto& last_time : queries){
		    int left_time = last_time - x;
		    ret.push_back(calculate_number(left,last_time));
	    }
	    return ret;
    }
};

int main(){
	return 0;
}
#endif
