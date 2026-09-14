/**
 * 84. 柱状图中最大的矩形
困难
相关标签
premium lock icon
相关企业
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

 

示例 1:



输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
示例 2：



输入： heights = [2,4]
输出： 4
 

提示：

1 <= heights.length <=105
0 <= heights[i] <= 104
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

// class Solution {
// public:
//     int largestRectangleArea(vector<int>& heights) {
//         vector<pair<int,int>> height_stack;
//         int cur_max =0,size = static_cast<int>(heights.size()),i;
//         for(i=0;i<size;++i){
//             //先比较与当前值的大小
//             int cur_val = heights[i];
//             cur_max =max(cur_max,cur_val);
//             //设置要放入栈的下标
//             int push_idx = i,array_size =static_cast<int>(height_stack.size());
//             //栈不为空，就计算栈内下标值与
//             while(array_size--){
//                 int top_idx = height_stack[array_size].first,top_val = height_stack[array_size].second;
//                 //如果当前值不大于栈顶值，那就直接把栈顶弹出，并修改,要入栈的下标为栈顶的下标
//                 int edge = top_val;
//                 if(cur_val <= top_val){
//                     push_idx = top_idx;
//                     edge = cur_val;
//                     height_stack.pop_back();
//                 }
//                 //计算面积
//                 cur_max = max(cur_max,edge * (i-top_idx+1));
//             }
//             //如果值不为0,把当前值放入栈内
//             if(cur_val)
//                 height_stack.emplace_back(push_idx,cur_val);
//         }
//         return cur_max;
//     }
// };
//寻找每个下标高度所能画出的最大矩形面积，然后找出最大的
//每个位置i能勾画的最大面积，必然是从当前位置向两边扩散，直到找到两边均严格小于当前高度的位置
//这一个区间内的矩形面积 = heights[i]*区间长度
//关键就是如何找到每个位置的左右最大区间，也就是找到左右第一个比当前高度底的下标
//可以维护一个单调栈，栈顶到栈底单调递减,这样栈顶的左区间就是栈顶与栈顶下一个元素下标距离
//右区间就是遍历到的第一个大于栈顶下标j，且heights[j]小于栈顶值的位置
//找到该下标以后，在回过头来计算栈顶的最大矩形
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        //存放元素下标
        heights.push_back(0);
        stack<int> idx_stk;
        int ret = 0,i,size = static_cast<int>(heights.size());
        for(i=0;i<size;++i){
            int cur_val = heights[i];
            //当栈不为空，并且栈顶下标的值严格大于当前元素时，计算栈顶元素所能画出的最大矩形面积
            int top_idx,top_val;
            while(!idx_stk.empty() && (top_val = heights[(top_idx = idx_stk.top())]) > cur_val){
                //计算栈顶的最大矩形
                idx_stk.pop();
                int left_idx = idx_stk.empty() ? 0 : idx_stk.top() +1;
                ret = max(ret,top_val * (i-left_idx));
            }
            //当前元素下标入栈
            idx_stk.push(i);
        }
        return ret;
    }
};

// int main(){
//     // vector<int> heights = {2,1,5,6,2,3};
//     // vector<int> heights = {2,4};
//     // vector<int> heights = {1,2,3,4,5};
//     vector<int> heights = {3,6,5,7,4,8,1,0};
//     // vector<int> heights = {9,1,0,5,6,3,9,3,5,8,9,0,6,4};
//     Solution sl;
//     cout << sl.largestRectangleArea(heights) << endl;
//     return 0;
// }