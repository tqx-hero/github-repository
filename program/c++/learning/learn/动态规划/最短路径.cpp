/*
   从 vector {{2,5},{2,5},{2,5},{2,5}}
    每组子数组代表到下一个顶点的2条不同长度的边，求从开始节点到终点的最短距离
*/
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
//要使总路径最短，就保证从后往前每个节点到终点的距离最短
//从后往前倒着遍历，每次选取到下一个节点更短的距离，直到起点
class Solution {

    public:
        vector<int> get_shortest_path(vector<vector<int>>& edge){
            int size =static_cast<int>(edge.size());
            vector<int> ret;
            vector<vector<int>> dp(size,vector<int>(edge[0].size(),0));
            dp[size-1][0] = edge[size-1][0];
            dp[size-1][1] = edge[size-1][1];
            int i;
            for(i=edge.size()-2;i>=0;--i){
                dp[i][0] = edge[i][0]+dp[i+1][0];
                dp[i][1] = edge[i][1]+dp[i+1][1];
            }
            if(dp[0][0] < dp[0][1])
                i =0;
            else 
                i=1;
            for(auto& vc: edge)
                ret.push_back(vc[i]);
            return ret;
        }
};

// int main(){
//     vector<vector<int>> edge{{2,5},{2,5},{2,5},{2,5}};
//     Solution sl;
//     const auto& vc = sl.get_shortest_path(edge);
//     for_each(vc.begin(),vc.end(),[](int x){cout << x << " ";});
//     cout << endl;
//     return 0;
// }