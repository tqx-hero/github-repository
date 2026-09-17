/**
 * Q2. 查找和最小的 K 对数字
中等
相关标签
premium lock icon
相关企业
给定两个以 非递减顺序排列 的整数数组 nums1 和 nums2 , 以及一个整数 k 。

定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2 。

请找到和最小的 k 个数对 (u1,v1),  (u2,v2)  ...  (uk,vk) 。

 

示例 1:

输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
输出: [[1,2],[1,4],[1,6]]
解释: 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
示例 2:

输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
输出: [[1,1],[1,1]]
解释: 返回序列中的前 2 对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3]
 

提示:

1 <= nums1.length, nums2.length <= 105
-109 <= nums1[i], nums2[i] <= 109
nums1 和 nums2 均为 升序排列
1 <= k <= 104
k <= nums1.length * nums2.length
 */
#include <vector>
#include <queue>
#include <iostream>
using namespace std;
//TODO
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
          // priority_queue<int,vector<int>,greater<int>> n1_queue{nums1.begin(),nums1.ebd()},n2_queue{nums2.begin(),nums2.end()};
          // vector<vector<int>> ret;
          // ret.reserve(k);
          // while(k--){
          //      int n1 = n1_queue.top(),n2 = n2_queue.top();
          //      ret.push_back(vector<int>{n1,n2});
          //      if(n1 > n2)
          //           n1_queue.pop();
          //      else if(n1 < n2)
          //           n2_queue.pop();
          //      else{
          //           //如果两者相同，先都出堆，在看第二个堆顶那个大

          //      }
          // }
    }
};

// int main(){
//     return 0;
// }