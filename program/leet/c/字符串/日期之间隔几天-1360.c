/**
  1360. 日期之间隔几天
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  请你编写一个程序来计算两个日期之间隔了多少天。

  日期以字符串形式给出，格式为 YYYY-MM-DD，如示例所示。



  示例 1：

  输入：date1 = "2019-06-29", date2 = "2019-06-30"
  输出：1
  示例 2：

  输入：date1 = "2020-01-15", date2 = "2019-12-31"
  输出：15


  提示：

  给定的日期是 1971 年到 2100 年之间的有效日期。
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int daysBetweenDates(char* date1, char* date2) {
    struct tm t1,t2;
    long long seconds;
    memset(&t1,0,sizeof(t1));
    memset(&t2,0,sizeof(t2));
    t1.tm_year = atoi(date1) - 1900;
    t1.tm_mon = atoi(date1 + 5) - 1;
    t1.tm_mday = atoi(date1 + 8);

    t2.tm_year = atoi(date2) - 1900;
    t2.tm_mon = atoi(date2 + 5) - 1;
    t2.tm_mday = atoi(date2 + 8);

    seconds = llabs(difftime(mktime(&t1),mktime(&t2)));
    return (int)(seconds / (24 * 3600));
}

int main(){
    //    char * date1 = "2020-01-15", *date2 = "2019-12-31";
    char * date1 = "2074-09-12", *date2 = "1983-01-08";
    fprintf(stdout,"%d\n",daysBetweenDates(date1,date2));
    exit(0);
}
