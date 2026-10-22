//
// Created by Administrator on 2026/6/19.
//
/**
* 3633. 最早完成陆地和水上游乐设施的时间 I
简单
相关标签
premium lock icon
相关企业
提示
给你两种类别的游乐园项目：陆地游乐设施 和 水上游乐设施。

陆地游乐设施
landStartTime[i] – 第 i 个陆地游乐设施最早可以开始的时间。
landDuration[i] – 第 i 个陆地游乐设施持续的时间。
水上游乐设施
waterStartTime[j] – 第 j 个水上游乐设施最早可以开始的时间。
waterDuration[j] – 第 j 个水上游乐设施持续的时间。
一位游客必须从 每个 类别中体验 恰好一个 游乐设施，顺序 不限 。

游乐设施可以在其开放时间开始，或 之后任意时间 开始。
如果一个游乐设施在时间 t 开始，它将在时间 t + duration 结束。
完成一个游乐设施后，游客可以立即乘坐另一个（如果它已经开放），或者等待它开放。
返回游客完成这两个游乐设施的 最早可能时间 。



示例 1:

输入：landStartTime = [2,8], landDuration = [4,1], waterStartTime = [6], waterDuration = [3]

输出：9

解释：

方案 A（陆地游乐设施 0 → 水上游乐设施 0）：
在时间 landStartTime[0] = 2 开始陆地游乐设施 0。在 2 + landDuration[0] = 6 结束。
水上游乐设施 0 在时间 waterStartTime[0] = 6 开放。立即在时间 6 开始，在 6 + waterDuration[0] = 9 结束。
方案 B（水上游乐设施 0 → 陆地游乐设施 1）：
在时间 waterStartTime[0] = 6 开始水上游乐设施 0。在 6 + waterDuration[0] = 9 结束。
陆地游乐设施 1 在 landStartTime[1] = 8 开放。在时间 9 开始，在 9 + landDuration[1] = 10 结束。
方案 C（陆地游乐设施 1 → 水上游乐设施 0）：
在时间 landStartTime[1] = 8 开始陆地游乐设施 1。在 8 + landDuration[1] = 9 结束。
水上游乐设施 0 在 waterStartTime[0] = 6 开放。在时间 9 开始，在 9 + waterDuration[0] = 12 结束。
方案 D（水上游乐设施 0 → 陆地游乐设施 0）：
在时间 waterStartTime[0] = 6 开始水上游乐设施 0。在 6 + waterDuration[0] = 9 结束。
陆地游乐设施 0 在 landStartTime[0] = 2 开放。在时间 9 开始，在 9 + landDuration[0] = 13 结束。
方案 A 提供了最早的结束时间 9。

示例 2:

输入：landStartTime = [5], landDuration = [3], waterStartTime = [1], waterDuration = [10]

输出：14

解释：

方案 A（水上游乐设施 0 → 陆地游乐设施 0）：
在时间 waterStartTime[0] = 1 开始水上游乐设施 0。在 1 + waterDuration[0] = 11 结束。
陆地游乐设施 0 在 landStartTime[0] = 5 开放。立即在时间 11 开始，在 11 + landDuration[0] = 14 结束。
方案 B（陆地游乐设施 0 → 水上游乐设施 0）：
在时间 landStartTime[0] = 5 开始陆地游乐设施 0。在 5 + landDuration[0] = 8 结束。
水上游乐设施 0 在 waterStartTime[0] = 1 开放。立即在时间 8 开始，在 8 + waterDuration[0] = 18 结束。
方案 A 提供了最早的结束时间 14。
 * @return
 */
//先分别计算2个项目的权重，即开始时间+持续时间->权重weight
//同时分别统计2个项目的权重最小值
//选出权重最小的那个项目，之后再从另一个项目里面选择：
//比如选出的最小权重项目w是陆上项目，那就开始遍历水上项目。
//查看水上项目各个开始时间是否大于w。
//小于等于w，则说明等w结束时这个项目已经开始了，就直接以：w+这个项目的持续时间，结果即为这个项目对应的最早结束时间，记录并更新
//如果大于w，说明w结束时这个项目还未开始，计算变成了：这个项目的开始时间+持续时间，结果就是这个项目对应的最早结束时间，记录并更新最小值min
//遍历完成，返回min
#define MIN(x,y) ((x) <= (y) ? (x) : (y))
#include <stdio.h>

int earliestFinishTime(int *landStartTime, int landStartTimeSize, int *landDuration, int landDurationSize,
                       int *waterStartTime, int waterStartTimeSize, int *waterDuration, int waterDurationSize) {
    int i = 0, landWeights[landStartTimeSize], landMinWeight = __INT32_MAX__,
            waterMinWeight = __INT32_MAX__
            , landMinTime = __INT32_MAX__, waterMinTime = __INT32_MAX__;
    for (; i < landStartTimeSize; i++) {
        int costs = landStartTime[i] + landDuration[i];
        landWeights[i] = costs;
        landMinWeight = MIN(landMinWeight, costs);
    }
    //计算开始项目为陆地时需要耗费的最少时间
    for (i = 0; i < waterStartTimeSize; i++) {
        int costs = waterStartTime[i] + waterDuration[i];
        waterMinWeight = MIN(waterMinWeight, costs);
        //陆地最小值分别与水上项目相加计算
        int curMinTime;
        if (waterStartTime[i] <= landMinWeight)
            curMinTime = landMinWeight + waterDuration[i];
        else
            curMinTime = costs;
        landMinTime = MIN(landMinTime, curMinTime);
    }
    //判断水上项目的最小权重是否超过当前统计的最小时间，超过直接返回
    if (waterMinWeight > landMinTime)
        return landMinTime;
    //没超过就再次统计开始项目为水上项目时的最短时间
    for (i = 0; i < landDurationSize; i++) {
        //陆地最小值分别与水上项目相加计算
        int curMinTime;
        if (landStartTime[i] <= waterMinWeight)
            curMinTime = waterMinWeight + landDuration[i];
        else
            curMinTime = landWeights[i];
        waterMinTime = MIN(waterMinTime, curMinTime);
    }
    return MIN(landMinTime, waterMinTime);
}

int main() {
    int landStartTime[] = {2, 8}, landDuration[] = {4, 1}, waterStartTime[] = {6}, waterDuration[] = {3};
    int res = earliestFinishTime(landStartTime, sizeof(landStartTime) / sizeof(int), landDuration,
                                 sizeof(landDuration) / sizeof(int)
                                 , waterStartTime, sizeof(waterStartTime) / sizeof(int), waterDuration,
                                 sizeof(waterDuration) / sizeof(int));
    printf("%d\n", res);
    return 0;
}
