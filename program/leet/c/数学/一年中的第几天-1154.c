/**
  1154. 一年中的第几天
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给你一个字符串 date ，按 YYYY-MM-DD 格式表示一个 现行公元纪年法 日期。返回该日期是当年的第几天。



  示例 1：

  输入：date = "2019-01-09"
  输出：9
  解释：给定日期是2019年的第九天。
  示例 2：

  输入：date = "2019-02-10"
  输出：41


  提示：

  date.length == 10
  date[4] == date[7] == '-'，其他的 date[i] 都是数字
  date 表示的范围从 1900 年 1 月 1 日至 2019 年 12 月 31 日
 */
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#if 0
//最简单的方法，直接使用strptime(3)转换，但是需要提前声明宏，力扣无法实现
int dayOfYear(char* date) {
    int ret;
    struct tm ctime;
    strptime(date,"%Y-%m-%d",&ctime);
    ret = ctime.tm_yday + 1;
    return ret;
}
#endif

int dayOfYear(char* date) {
    struct tm ctime;
    memset(&ctime,0,sizeof(ctime));
    ctime.tm_year = atoi(date) - 1900;
    ctime.tm_mon = atoi(date + 5) - 1;
    ctime.tm_mday = atoi(date + 8);
    mktime(&ctime);
    return ctime.tm_yday + 1;
}

int main(){
//    char * date = "2019-01-09";
    char * date = "2019-02-10";
    fprintf(stdout,"%d\n",dayOfYear(date));
    exit(0);
}
