/**
 * 51. N 皇后
困难
相关标签
premium lock icon
相关企业
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。

n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。

每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

 

示例 1：


输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。
示例 2：

输入：n = 1
输出：[["Q"]]
 

提示：

1 <= n <= 9
 */
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution {
    vector<vector<string>> ret;

    void set_mark(vector<vector<int>>& visited,int n,int x,int y){
        //x轴
        for_each(visited[x].begin(),visited[x].end(),[](int& m){m =1;});
        //y轴
        for(int j=0;j<n;j++)
            visited[j][y] =1;
        //斜线
        int sx,sy;
        for(sx=x-1,sy=y-1;sx >=0 && sy >= 0 ;sx--,sy--)
            visited[sx][sy] = 1;
        for(sx = x+1,sy = y+1; sx < n && sy < n ; sx++,sy++)
            visited[sx][sy] =1;
        //反斜线
        for(sx = x-1,sy = y+1;sx >=0 && sy < n ;sx--,sy++)
            visited[sx][sy] =1;
        for(sx = x+1,sy = y-1;sx < n && sy >= 0;sx++,sy--)
            visited[sx][sy] =1;
    }

    void dfs(int n,int x,vector<vector<int>>& visited,vector<string>& vc){
        //如果行遍历结束，统计该可行结果
        if(x >= n){
            ret.push_back(vc);
            return;
        }
        //该行还没有放入皇后，搜查有无可放入位置
        int j;
        for(j = 0 ; j < n ;++j){
            //如果当前行全部被标记，皇后没地方放，直接返回
            if(visited[x][j])
                continue;
            //拼接字符串，放入vc,设置标记
            string str(n,'.');
            str[j] ='Q';
            vc.push_back(str);
            vector<vector<int>> temp_visited(visited);
            set_mark(temp_visited,n,x,j);
            //放置下一行的皇后
            dfs(n,x+1,temp_visited,vc);
            vc.pop_back();
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        if(n==1)
            return vector<vector<string>>{vector<string>{"Q"}};
        vector<vector<int>> visited(n,vector<int>(n,0));
        int i,j;
        for(i=0;i<n;++i)
            visited[i][i] = 1;
        for(i=0,j=n-1;i < n;i++,j--)
            visited[i][j] = 1;
        // visited.assign(n,vector<int>(n));
        vector<string> vc;
        vc.reserve(n);
        dfs(n,0,visited,vc);
        return ret;
    }
};

// int main(){
//     int n =1;
//     Solution sl;
//     const auto & vcet = sl.solveNQueens(n);
//     for_each(vcet.begin(),vcet.end(),[](const vector<string>& vc){
//         for_each(vc.begin(),vc.end(),[](const string& str){cout << str << " ";});
//         cout << endl;
//     });
//     return 0;
// }