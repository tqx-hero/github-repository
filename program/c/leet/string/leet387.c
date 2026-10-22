#include <stdio.h>
//
// Created by Administrator on 2026/6/27.
//
/**
* 387. 字符串中的第一个唯一字符
简单
相关标签
premium lock icon
相关企业
给定一个字符串 s ，找到 它的第一个不重复的字符，并返回它的索引 。如果不存在，则返回 -1 。



示例 1：

输入: s = "leetcode"
输出: 0
示例 2:

输入: s = "loveleetcode"
输出: 2
示例 3:

输入: s = "aabb"
输出: -1


提示:

1 <= s.length <= 105
s 只包含小写字母
 * @return
 */
//新建1个数组，长度为26，用于存放a~z这26个英文单词的出现次数
//扫描2遍字符串。第一遍统计词频放入数组，第二次找到第一个count=1的字符下标
int firstUniqChar(char *s) {
    int counts[26] = {0}, i = 0;
    char ch;
    for (; (ch = s[i]) != '\0'; i++)
        counts[ch - 'a']++;
    for (i = 0; (ch = s[i]) != '\0'; i++) {
        if (counts[ch - 'a'] == 1)
            return i;
    }
    return -1;
}

int main() {
    char *s = "aabb";
    printf("%d\n", firstUniqChar(s));
    return 0;
}
