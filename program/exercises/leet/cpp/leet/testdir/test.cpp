/**
 * 79. 单词搜索
中等
相关标签
premium lock icon
相关企业
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

 

示例 1：


输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "ABCCED"
输出：true
示例 2：


输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "SEE"
输出：true
示例 3：


输入：board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "ABCB"
输出：false
 

提示：

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board 和 word 仅由大小写英文字母组成
 

进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在 board 更大的情况下可以更快解决问题？
 */
#include <vector>
#include <string>
#include <iostream>
#include <array>
using namespace std;
#define FIND_CONFIG if(find) \
                        return;
//优化思路：
//1、可以统计一下模式串的各单词词频在二维数组中是否有足够数量。数量不足肯定不能拼出来。
//2、再统计一下模式串首尾字符的词频，从词频更小的那一头开始匹配，这样就减少无用的递归次数.
class Solution {
    int row_size,col_size;
    bool find =false,order;
    void helper(vector<vector<char>>& board, string& word,int cur_index,int x,int y,
        vector<vector<int>>& visited){
        if(cur_index >= word.size() || cur_index < 0)
        {
            find =true;
            return;
        } 
        if(x >=row_size || x <0 || y >= col_size || y < 0)
            return;
        //如果当前字符匹配字符串字符，且还没被标记
        if(board[x][y] == word[cur_index] && !visited[x][y]){
            visited[x][y] = 1;
            int next_index = order ? cur_index+1 : cur_index -1;
            helper(board,word,next_index,x-1,y,visited);
            FIND_CONFIG
            helper(board,word,next_index,x+1,y,visited);
            FIND_CONFIG
            helper(board,word,next_index,x,y-1,visited);
            FIND_CONFIG
            helper(board,word,next_index,x,y+1,visited);
            FIND_CONFIG
            visited[x][y] =0;
        }
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        int str_size = static_cast<int>(word.size());
        row_size = static_cast<int>(board.size());
        col_size = static_cast<int>(board[0].size());
        //统计模式串的词频
        array<int,64> s_char_cnt{0},v_cnt{0};
        for(auto ch : word)
            s_char_cnt[ch - 'A']++;
        int i,j;
        for(i=0;i<row_size;++i)
            for(j=0;j<col_size;j++)
                v_cnt[board[i][j] -'A']++;
        //查看数组中字符个数是否符合模式串的要求
        for(i =0;i<s_char_cnt.size();++i)
            if(s_char_cnt[i] > v_cnt[i])
                return false;
        vector<vector<int>> visited(row_size,vector<int>(col_size,0));
        order = s_char_cnt[word[0]-'A'] <= s_char_cnt[word[str_size-1]-'A'];
        for(i=0;i<row_size;++i){
            for(j=0;j<col_size;++j){
                helper(board,word,order ? 0 : str_size - 1 ,i,j,visited);
                if(find)
                    return true;
            }
        }
        return false;
    }
};

// int main(){
//     // vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
//     // string word = "ABCCED";
//     //board = [['A','B','C','E'],['S','F','C','S'],['A','D','E','E']], word = "SEE"
//     // vector<vector<char>> board = {{'A','B','C','E'},{'S','F','C','S'},{'A','D','E','E'}};
//     // string word = "SEE";
//     // [["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","A"],["A","A","A","A","A","B"],["A","A","A","A","B","A"]]
//     vector<vector<char>> board = {
//         {'A','A','A','A','A','A'},
//         {'A','A','A','A','A','A'},
//         {'A','A','A','A','A','A'},
//         {'A','A','A','A','A','A'},
//         {'A','A','A','A','A','B'},
//         {'A','A','A','A','B','A'}
//     };
//     string word = "AAAAAAAAAAAAABB";
//     Solution sl;
//     cout << sl.exist(board,word) << endl;
//     return 0;
// }