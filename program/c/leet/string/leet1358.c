#include <stdio.h>
#include <string.h>
//
// Created by Administrator on 2026/6/30.
//
/**
* 1358. 包含所有三种字符的子字符串数目
中等
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s ，它只包含三种字符 a, b 和 c 。

请你返回 a，b 和 c 都 至少 出现过一次的子字符串数目。



示例 1：

输入：s = "abcabc"
输出：10
解释：包含 a，b 和 c 各至少一次的子字符串为 "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" 和 "abc" (相同字符串算多次)。
示例 2：

输入：s = "aaacb"
输出：3
解释：包含 a，b 和 c 各至少一次的子字符串为 "aaacb", "aacb" 和 "acb" 。
示例 3：

输入：s = "abc"
输出：1


提示：

3 <= s.length <= 5 x 10^4
s 只包含字符 a，b 和 c 。
 * @return
 */
//双指针，窗口大小size>=3，统计窗口内的a、b、c的字符数量
//left固定，right移动，直到a、b、c三个字符均至少为1，统计后面字符的数量count+1；
//如果size>=3,left++,查看三个字符是否满足条件，如果满足，增加count+1个数量
//直到不满足条件为止，此时继续固定left，right++，直到满足条件，再次循环以上步骤，直到right超过字符串长度
int numberOfSubstrings(char *s) {
    int ans = 0, counts[3] = {0};
    int size = (int) strlen(s);
    int left = 0, right = 0;
    for (; right < size; right++) {
        counts[s[right] - 'a']++;
        while (counts[0] >= 1 && counts[1] >= 1 && counts[2] >= 1) {
            ans += size - right;
            counts[s[left++] - 'a']--;
        }
    }
    return ans;
}

int main() {
    char *s = "aaacb";
    // char *s = "abcabc";
    printf("%d\n", numberOfSubstrings(s));
    return 0;
}
