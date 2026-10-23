//
// Created by Administrator on 2026/8/15.
//
/**
* 罗马数字转整数
罗马数字包含以下七种字符: I， V， X， L，C，D 和 M。
字符          数值
I             1
V             5
X             10
L             50
C             100
D             500
M             1000
例如， 罗马数字 2 写做 II ，即为两个并列的 1 。12 写做 XII ，即为 X + II 。 27 写做  XXVII, 即为 XX + V + II 。
通常情况下，罗马数字中小的数字在大的数字的右边。但也存在特例，例如 4 不写做 IIII，而是 IV。数字 1 在数字 5 的左边，所表示的数等于大数 5 减小数 1 得到的数值 4 。同样地，数字 9 表示为 IX。这个特殊的规则只适用于以下六种情况：
• I 可以放在 V (5) 和 X (10) 的左边，来表示 4 和 9。
• X 可以放在 L (50) 和 C (100) 的左边，来表示 40 和 90。 
• C 可以放在 D (500) 和 M (1000) 的左边，来表示 400 和 900。
给定一个罗马数字，将其转换成整数。
 * @return
 */
#include <iostream>
#include <string>
using namespace std;
#define CASE(chs,value) case chs: \
                        ret = value; \
                        break;
#define CONFIG_NEGATIVE(ch11,ch22,ch33)  (ch == ch11 && (ch2 == ch22 || ch2 == ch33))
class Solution {
    int getNum(char ch) {
        int ret;
        switch (ch) {
            CASE('I', 1)
            CASE('V', 5)
            CASE('X', 10)
            CASE('L', 50)
            CASE('C', 100)
            CASE('D', 500)
            CASE('M', 1000)
            default:
                ret = 0;
                break;
        }
        return ret;
    }

public:
    int romanToInt(string s) {
        int size = static_cast<int>(s.size()), total_sum = 0, i = 0;
        for (; i < size - 1; i++) {
            char ch = s[i], ch2 = s[i + 1];
            int num = getNum(ch);
            if (CONFIG_NEGATIVE('I', 'V', 'X')
                ||
                CONFIG_NEGATIVE('X', 'L', 'C')
                ||
                CONFIG_NEGATIVE('C', 'D', 'M')
            )
                num = -num;
            total_sum += num;
        }
        return total_sum + getNum(s[i]);
    }
};

// int main() {
//     string str = "MCMXCIV";
//     Solution sl;
//     std::cout << sl.romanToInt(str) << endl;
//     return 0;
// }
