//
// Created by Administrator on 2026/6/7.
//
/**
* 316. 去除重复字母
中等
相关标签
premium lock icon
相关企业
提示
给你一个字符串 s ，请你去除字符串中重复的字母，使得每个字母只出现一次。需保证 返回结果的字典序最小（要求不能打乱其他字符的相对位置）。



示例 1：

输入：s = "bcabc"
输出："abc"
示例 2：

输入：s = "cbacdcbc"
输出："acdb"


提示：

1 <= s.length <= 104
s 由小写英文字母组成


注意：该题与 1081 https://leetcode.cn/problems/smallest-subsequence-of-distinct-characters 相同
 * @return
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *removeDuplicateLetters(char *s) {
    int len = (int) strlen(s);
    if (len == 1)
        return s;
    //由于都是小写字母,以ascii-'a' 作为key
    int contains[26], nums[26];
    memset(contains, 0, 26 * sizeof(int));
    memset(nums, 0, 26 * sizeof(int));
    char *ret = malloc(27);
    //统计字符出现的个数
    int i = 0;
    for (; i < len; ++i)
        nums[s[i] - 'a']++;
    int j = 0;
    for (i = 0; i < len; ++i) {
        char c = s[i];
        //栈内不存在
        if (!contains[c - 'a']) {
            //如果栈顶大于当前值
            //需要判断栈顶元素是否还有其他的
            char p;
            while (j > 0 && (p = ret[j-1]) > c) {
                //如果后面仍然有栈顶元素，那就应该把它弹出去，因为它比当前元素大
                //按照字典序要求肯定是要排在c后面，所以需要弹栈
                if (nums[p-'a'] > 0) {
                    j--;
                    contains[p - 'a'] = 0;
                } else
                    break;
            }
            //当栈空或者栈顶元素小于当前元素，入栈
            ret[j++] = c;
            contains[c - 'a'] = 1;
        }
        //栈内存在，直接丢弃
        nums[c - 'a']--;
    }
    ret[j] = '\0';
    return ret;
}

int main() {
    char *s = "bcabc";
    // char *s = "abacb";
    // char *s = "bcabc";
    // char *s = "cbacdcbc";
    char *ret = removeDuplicateLetters(s);
    printf("%s\n", ret);
    free(ret);
    ret = NULL;
    return 0;
}
