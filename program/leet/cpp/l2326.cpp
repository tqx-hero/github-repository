//
// Created by Administrator on 2026/7/16.
//
/**
* 2326. 螺旋矩阵 IV
中等
相关标签
premium lock icon
相关企业
提示
给你两个整数：m 和 n ，表示矩阵的维数。

另给你一个整数链表的头节点 head 。

请你生成一个大小为 m x n 的螺旋矩阵，矩阵包含链表中的所有整数。链表中的整数从矩阵 左上角 开始、顺时针 按 螺旋 顺序填充。如果还存在剩余的空格，则用 -1 填充。

返回生成的矩阵。



示例 1：


输入：m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
输出：[[3,0,2,6,8],[5,0,-1,-1,1],[5,2,4,9,7]]
解释：上图展示了链表中的整数在矩阵中是如何排布的。
注意，矩阵中剩下的空格用 -1 填充。
示例 2：


输入：m = 1, n = 4, head = [0,1,2]
输出：[[0,1,2,-1]]
解释：上图展示了链表中的整数在矩阵中是如何从左到右排布的。
注意，矩阵中剩下的空格用 -1 填充。


提示：

1 <= m, n <= 105
1 <= m * n <= 105
链表中节点数目在范围 [1, m * n] 内
0 <= Node.val <= 1000
 * @return
 */
#include <iostream>
#include "../link/ListNode.h"
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<int> > spiralMatrix(int m, int n, ListNode *head) {
        vector<vector<int> > matrix(m, vector<int>(n, -1));
        ListNode *cur = head;
        int i, j, leftRow = 0, rightRow = m - 1, leftCol = 0, rightCol = n - 1;
        while (cur) {
            i = leftRow, j = leftCol;
            //按行填充
            while (cur && j <= rightCol) {
                matrix[i][j++] = cur->val;
                cur = cur->next;
            }
            //行到头以后，开始按照列补充
            leftRow++;
            i = leftRow, j = rightCol;
            while (cur && i <= rightRow) {
                matrix[i++][j] = cur->val;
                cur = cur->next;
            }
            rightCol--;
            i = rightRow, j = rightCol;
            while (cur && j >= leftCol) {
                matrix[i][j--] = cur->val;
                cur = cur->next;
            }
            rightRow--;
            i = rightRow, j = leftCol;
            while (cur && i >= leftRow) {
                matrix[i--][j] = cur->val;
                cur = cur->next;
            }
            leftCol++;
        }
        return matrix;
    }
};

// int main() {
//     //m = 3, n = 5, head = [3,0,2,6,8,1,7,9,4,2,5,5,0]
//     int m = 3, n = 5;
//     ListNode l13(0);
//     ListNode l12(5, &l13);
//     ListNode l11(5, &l12);
//     ListNode l10(2, &l11);
//     ListNode l9(4, &l10);
//     ListNode l8(9, &l9);
//     ListNode l7(7, &l8);
//     ListNode l6(1, &l7);
//     ListNode l5(8, &l6);
//     ListNode l4(6, &l5);
//     ListNode l3(2, &l4);
//     ListNode l2(0, &l3);
//     ListNode l1(3, &l2);
//     Solution sl;
//     vector<vector<int> > matrix = sl.spiralMatrix(m, n, &l1);
//     for (int i = 0; i < matrix.size(); i++) {
//         for (int j = 0; j < matrix[0].size(); j++) {
//             cout << matrix[i][j] << "\t";
//         }
//         cout << endl;
//     }
//     return 0;
// }
