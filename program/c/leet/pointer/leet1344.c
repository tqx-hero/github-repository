#include <stdio.h>
//
// Created by Administrator on 2026/6/18.
//
/**
*1344. 时钟指针的夹角
￼
中等
￼
相关标签
￼
相关企业
￼
提示
￼
给你两个数 hour 和 minutes 。请你返回在时钟上，由给定时间的时针和分针组成的较小角的角度（60 单位制）。 
示例 1：
输入：
hour = 12, minutes = 30
输出：
165
 * @return
 */
//快慢指针，minutes为快指针，移动60格转360°。hour为慢指针，minutes移动60格，它移动5格，也就是30°
//所以这题是先要看minutes是多少，除以60得到比例k在乘以360°就代表当前快指针相对于0位置转了多少度角。
//hour慢指针需要先看是几点，由于是12分制，所以需要先确定整点时的hour指针偏移是多少，也就是hour的基址，计算h=hour%12
//在需要用分钟指针已经旋转的比例k*30°，得到同一时刻hour从整点位置又转了多少度，与基址h相加，即为hour相对于0转的角度
//最后minutes与hour的角度相减，取绝对值即为两者之间的夹角


double angleClock(int hour, int minutes) {
    double minutes_rate = 360.00f,hour_rate = 30.00f,minutes_base = 60.00f;
    int hour_base = 12;
    double rate = minutes /minutes_base;
    double minutes_angle = rate *minutes_rate;
    double hour_angle = (hour%hour_base+rate) * hour_rate;
    double result =minutes_angle >= hour_angle ? minutes_angle-hour_angle : hour_angle - minutes_angle;
    return result > 180.00f ? minutes_rate-result :result;
}

int main() {
    // int hour = 12,minutes =30;
    int hour = 1,minutes =57;
    printf("%f\n",angleClock(hour,minutes));
    return 0;
}