/**
 * Q3. 柱状图中最大的矩形
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
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int size = static_cast<int>(heights.size());
        stack<int> idx_stack;
        idx_stack.push(0);
        int i=1,max_area = 0;
        for(;i<size;++i){
            while(heights[idx_stack.top()] > heights[i]){
                int top_idx = idx_stack.top();
                idx_stack.pop();
                int left_idx = idx_stack.empty() ? 0 : idx_stack.top();
                max_area = max(max_area,(i-left_idx) * heights[top_idx]);
            }
            idx_stack.push(i);
        }
        while(!idx_stack.empty()){
            int top_idx = idx_stack.top();
            idx_stack.pop();
            int left_idx = idx_stack.empty() ? 0 : idx_stack.top();
            max_area = max(max_area,heights[top_idx] * (top_idx - left_idx));
        }
        return max_area;
    }
};

int main(){
    vector<int> heights{2,1,5,6,2,3};
    Solution sl;
    cout << sl.largestRectangleArea(heights) << endl;
    return 0;
}