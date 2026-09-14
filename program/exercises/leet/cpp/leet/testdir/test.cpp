/**
 * 295. 数据流的中位数
困难
相关标签
premium lock icon
相关企业
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。

例如 arr = [2,3,4] 的中位数是 3 。
例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
实现 MedianFinder 类:

MedianFinder() 初始化 MedianFinder 对象。

void addNum(int num) 将数据流中的整数 num 添加到数据结构中。

double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5 以内的答案将被接受。

示例 1：

输入
["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
[[], [1], [2], [], [3], []]
输出
[null, null, null, 1.5, null, 2.0]

解释
MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0
提示:

-105 <= num <= 105
在调用 findMedian 之前，数据结构中至少有一个元素
最多 5 * 104 次调用 addNum 和 findMedian
 */
#include <queue>
#include <iostream>
using namespace std;
//使用两个堆维护数据流
//大顶堆存放较小的那一半值，小顶堆存放较大的那一半值
//维护两个堆的数量平衡，使得数量满足大顶堆 <= 小顶堆+1
//在获取中位数时，奇数个就取大顶堆堆顶，偶数个就取(大堆顶+小堆顶) /2;数据超不过32位整型范围无需关心越界问题
class MedianFinder {
    priority_queue<int,vector<int>,greater<int>> min_heap;
    priority_queue<int> max_heap;

    //平衡堆
    void balance_heap(){
        int max_heap_size = max_heap.size(),min_heap_size = min_heap.size();
        if(max_heap_size == min_heap_size || max_heap_size == min_heap_size+1)
            return;
            //大顶堆数量过多,堆顶放入小顶堆
        if(max_heap_size > min_heap_size){
            min_heap.push(max_heap.top());
            max_heap.pop();
        }else{
            //小顶堆数量过多，堆顶放入大顶堆
            max_heap.push(min_heap.top());
            min_heap.pop();
        }
    }

public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        if(max_heap.empty()){
            max_heap.push(num);
            return;
        }
        //大小堆都不为空，那就比较num与大顶堆堆顶大小，大于堆顶直接入小顶堆，小于等于堆顶入大顶堆，再进行数量平衡
        int max_val = max_heap.top();
        if(max_val < num)
            min_heap.push(num);
        else
            max_heap.push(num);
        //平衡两个堆的元素数量,使大顶堆最多比小顶堆大1
        if(max_heap.size() > min_heap.size()+1 || min_heap.size() > max_heap.size())
            balance_heap();
    }
    
    double findMedian() {
        int total_size = max_heap.size()+min_heap.size();
        //奇数个，取大顶堆堆顶
        if(total_size %2)
            return max_heap.top();
        else
            return (static_cast<double>(max_heap.top()) + static_cast<double>(min_heap.top())) /2;
    }
};
/* MedianFinder medianFinder = new MedianFinder();
medianFinder.addNum(1);    // arr = [1]
medianFinder.addNum(2);    // arr = [1, 2]
medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
medianFinder.addNum(3);    // arr[1, 2, 3]
medianFinder.findMedian(); // return 2.0 */
// int main(){
//     MedianFinder medianFinder;
//     medianFinder.addNum(1);
//     medianFinder.addNum(2);
//     cout << medianFinder.findMedian() << endl;
//     medianFinder.addNum(3);
//     cout << medianFinder.findMedian() << endl;
//     return 0;
// }