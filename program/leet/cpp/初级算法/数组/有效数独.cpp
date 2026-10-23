//
// Created by Administrator on 2026/8/10.
//

/**
* 有效的数独
请你判断一个 9 x 9 的数独是否有效。只需要 根据以下规则 ，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
  

注意：

一个有效的数独（部分已被填充）不一定是可解的。
只需要根据以上规则，验证已经填入的数字是否有效即可。
空白格用 '.' 表示。

作者：LeetCode
链接：https://leetcode.cn/leetbook/read/top-interview-questions-easy/x2f9gg/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
 * @return
 */
#include <iostream>
#include <vector>
using namespace std;

class Solution {
    bool isMatch(vector<vector<char> > &board, int row_begin, int col_begin) {
        int blockBuckets[9]{0};
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char ch = board[row_begin + i][col_begin + j];
                if (ch == '.')
                    continue;
                if (blockBuckets[ch - '1'])
                    return false;
                blockBuckets[ch - '1']++;
            }
        }
        return true;
    }

public:
    bool isValidSudoku(vector<vector<char> > &board) {
        for (auto &rows: board) {
            int rowBuckets[9]{0};
            for (auto ch: rows) {
                if (ch == '.')
                    continue;
                if (rowBuckets[ch - '1'])
                    return false;
                rowBuckets[ch - '1']++;
            }
        }
        int i, j;
        for (i = 0; i < 9; i++) {
            int colBuckets[9]{0};
            for (j = 0; j < 9; j++) {
                char ch = board[j][i];
                if (ch == '.')
                    continue;
                if (colBuckets[ch - '1'])
                    return false;
                colBuckets[ch - '1']++;
            }
        }
        return isMatch(board, 0, 0) && isMatch(board, 3, 0)
               && isMatch(board, 6, 0) && isMatch(board, 0, 3)
               && isMatch(board, 0, 6) && isMatch(board, 3, 3)
               && isMatch(board, 3, 6) && isMatch(board, 6, 3)
               && isMatch(board, 6, 6);
    }
};

// int main() {
//     /*[["5","3",".",".","7",".",".",".","."],
//      *["6",".",".","1","9","5",".",".","."],
//      *[".","9","8",".",".",".",".","6","."],
//      *["8",".",".",".","6",".",".",".","3"],
//      *["4",".",".","8",".","3",".",".","1"],
//      *["7",".",".",".","2",".",".",".","6"],
//      *[".","6",".",".",".",".","2","8","."],
//      *[".",".",".","4","1","9",".",".","5"],
//      *[".",".",".",".","8",".",".","7","9"]]*/
//     vector<vector<char> > board{
//         {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
//         {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
//         {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
//         {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
//         {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
//         {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
//         {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
//         {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
//         {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
//     };
//     Solution sl;
//     cout << sl.isValidSudoku(board) << endl;
//     return 0;
// }
