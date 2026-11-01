//
// Created by Administrator on 2026/6/22.
//
/**
* 1189. “气球” 的最大数量
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 text，你需要使用 text 中的字母来拼凑尽可能多的单词 "balloon"（气球）。

字符串 text 中的每个字母最多只能被使用一次。请你返回最多可以拼凑出多少个单词 "balloon"。



示例 1：



输入：text = "nlaebolko"
输出：1
示例 2：



输入：text = "loonbalxballpoon"
输出：2
示例 3：

输入：text = "leetcode"
输出：0


提示：

1 <= text.length <= 104
text 全部由小写英文字母组成


注意：本题与 2287. 重排字符形成目标字符串 相同。
 * @return
 */

#include <stdio.h>
#include <string.h>

int maxNumberOfBalloons(char *text) {
    int text_arr[26] = {0};
    int i = 0;
    char ch;
    for (; (ch = text[i]) != '\0'; i++)
        text_arr[ch - 'a']++;
    int ans = 0;
    while (text_arr[1]-- >= 1 && text_arr[0]-- >= 1 && text_arr['l' - 'a'] >= 2
           && text_arr['o' - 'a'] >= 2 && text_arr[
               'n' - 'a']-- >= 1) {
        ans++;
        text_arr['o' - 'a'] -= 2;
        text_arr['l' - 'a'] -= 2;
    }
    return ans;
}

int main() {
    char *str = "nlaebolko";
    printf("%d\n", maxNumberOfBalloons(str));
    return 0;
}
