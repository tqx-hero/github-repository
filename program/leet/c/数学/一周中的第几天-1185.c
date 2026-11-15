/**
 *
 * 1185. 一周中的第几天
简单
相关标签
premium lock icon
相关企业
提示
给你一个日期，请你设计一个算法来判断它是对应一周中的哪一天。

输入为三个整数：day、month 和 year，分别表示日、月、年。

您返回的结果必须是这几个值中的一个 {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}。

注意：1971 年 1 月 1 日是星期五。



示例 1：

输入：day = 31, month = 8, year = 2019
输出："Saturday"
示例 2：

输入：day = 18, month = 7, year = 1999
输出："Sunday"
示例 3：

输入：day = 15, month = 8, year = 1993
输出："Sunday"


提示：

给出的日期一定是在 1971 到 2100 年之间的有效日期。
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *dayOfTheWeek(int day, int month, int year)
{
    char *buf;
    struct tm ctime;
    memset(&ctime, 0, sizeof(ctime));
    ctime.tm_mday = day;
    ctime.tm_mon = month - 1;
    ctime.tm_year = year - 1900;
    if (mktime(&ctime) == (time_t)-1)
    {
        perror("mktime()");
        exit(1);
    }
    buf = malloc(16);
    if (!buf)
    {
        perror("malloc()");
        exit(1);
    }

    strftime(buf, 16, "%A", &ctime);
    return buf;
}

int main()
{
    int day = 31, month = 8, year = 2019;
    char *buf = dayOfTheWeek(day, month, year);
    fprintf(stdout, "%s\n", buf);
    free(buf);
    exit(0);
}