//
// Created by Administrator on 2026/7/6.
//
/**
* 3120. 统计特殊字母的数量 I
简单
相关标签
premium lock icon
相关企业
提示
给你一个字符串 word。如果 word 中同时存在某个字母的小写形式和大写形式，则称这个字母为 特殊字母 。

返回 word 中 特殊字母 的数量。



示例 1:

输入：word = "aaAbcBC"

输出：3

解释：

word 中的特殊字母是 'a'、'b' 和 'c'。

示例 2:

输入：word = "abc"

输出：0

解释：

word 中不存在大小写形式同时出现的字母。

示例 3:

输入：word = "abBCab"

输出：1

解释：

word 中唯一的特殊字母是 'b'。



提示：

1 <= word.length <= 50
word 仅由小写和大写英文字母组成。
 * @return
 */
//开一个58size大小的数组counts，用来存放大小写字母数量
//A的ASCII=65 ，a的ASCII=97，两者差32
//令数组下标 = 字母-'A',即0~25存放A~Z，32~57存放a~z
//1、遍历字符串，统计出每个字符的出现次数，放入counts数组内。
//2、遍历counts数组的0~25下标，即遍历A~Z所有大写字母
//统计大写字母个数不为0且+32后值，也就是它对应的小写字母不为0的，统计这个字符个数，返回结果
int numberOfSpecialChars(char *word) {
    int counts[58] = {0}, i, ret = 0;
    char ch;
    //遍历字符串统计词频
    for (i = 0; (ch = word[i]) != '\0'; i++)
        counts[ch - 'A']++;
    for (i = 0; i < 26; i++)
        if (counts[i] && counts[i + 32])
            ret++;
    return ret;
}

int main() {
    return 0;
}
