#include <stdio.h>
#include <stdlib.h>
//
// Created by Administrator on 2026/6/1.
//
/**
*
代码
测试用例
测试用例
测试结果
2833. 距离原点最远的点
简单
相关标签
premium lock icon
相关企业
提示
给你一个长度为 n 的字符串 moves ，该字符串仅由字符 'L'、'R' 和 '_' 组成。字符串表示你在一条原点为 0 的数轴上的若干次移动。

你的初始位置就在原点（0），第 i 次移动过程中，你可以根据对应字符选择移动方向：

如果 moves[i] = 'L' 或 moves[i] = '_' ，可以选择向左移动一个单位距离
如果 moves[i] = 'R' 或 moves[i] = '_' ，可以选择向右移动一个单位距离
返回在移动 n 次之后，可以到达的距离原点 最远 的点 到原点的距离。



示例 1：

输入：moves = "L_RL__R"
输出：3
解释：可以到达的距离原点 0 最远的点是 -3 ，移动的序列为 "LLRLLLR" 。
示例 2：

输入：moves = "_R__LL_"
输出：5
解释：可以到达的距离原点 0 最远的点是 -5 ，移动的序列为 "LRLLLLL" 。
示例 3：

输入：moves = "_______"
输出：7
解释：可以到达的距离原点 0 最远的点是 7 ，移动的序列为 "RRRRRRR" 。


提示：

1 <= moves.length == n <= 50
moves 仅由字符 'L'、'R' 和 '_' 组成
 */
//R表示右移，L表示左移，_既可以左移又可以右移,具体要看最终位置是在左边还是右边
//所以咱们只要定位到除了_之外的其它字符，就能确定位置，然后让_赋值L或者R即可
//遍历字符串：令R=1表示右移+1，L=-1，表示左移-1，同时统计_的数量
//计算完成的结果如果>0表示在右边，<0表示在左边。
//不管大于还是小于0，都去绝对值，加上_的数量即可
int furthestDistanceFromOrigin(char *moves) {
    int count = 0, sum = 0;
    char c;
    for (int i = 0; (c = *(moves + i)) != '\0'; ++i) {
        if (c == 'R')
            sum++;
        else if (c == 'L')
            sum--;
        else
            count++;
    }
    //取sum的绝对值，加上_数量count，即为最远距离
    return abs(sum)+count;
}

// int main() {
//     char a[] ="_______";
//     int f = furthestDistanceFromOrigin(a);
//     printf("%d\n",f);
//     return 0;
// }
