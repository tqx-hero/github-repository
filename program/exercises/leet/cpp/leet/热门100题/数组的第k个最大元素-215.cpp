/**
 * 215. 数组中的第K个最大元素
中等
相关标签
premium lock icon
相关企业
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。

 

示例 1:

输入: [3,2,1,5,6,4], k = 2
输出: 5
示例 2:

输入: [3,2,3,1,2,4,5,5,6], k = 4
输出: 4
 

提示：

1 <= k <= nums.length <= 105
-104 <= nums[i] <= 104
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <array>
#include <queue>
using namespace std;
// //1、使用堆无脑排列
// class Solution {
// public:
//     int findKthLargest(vector<int>& nums, int k) {
//         priority_queue<int> max_heap{nums.begin(),nums.end()};
//         int ret;
//         while(k--){
//             ret = max_heap.top();
//             max_heap.pop();
//         }
//         return ret;
//     }
// };
//2、使用分治思想，将区间缩小成一个个的子问题
// class Solution {
//     template<typename T = int>
//     struct SortByMiddle
//     {
//         _GLIBCXX14_CONSTEXPR 
//        bool operator()(const vector<T>& t1, const vector<T>& t2) const{
//             return t1[(static_cast<int>(t1.size()) -1) /2] > t2[(static_cast<int>(t2.size()) -1 )/2 ];
//        }
//     };

// public:
//     int findKthLargest(vector<int>& nums, int k) {
//         //将数组拆分成5个一组，不足5个直接排序
//         int size = static_cast<int>(nums.size());
//         if(size <=5){
//             sort(nums.begin(),nums.end(),greater<int>{});
//             return nums[k-1];
//         }
//         //拆分数组
//         vector<vector<int>> temp_vc;
//         int i,j;
//         for(i=0;i<size;){
//             vector<int> temp;
//             for(j=0;j<5 && i<size;++i,j++)
//                 temp.push_back(nums[i]);
//             temp_vc.push_back(temp);
//         }
//         //对每一个子数组进行排序,规模较小(子数组只有5个)
//         for_each(temp_vc.begin(),temp_vc.end(),[](vector<int>& v){
//             sort(v.begin(),v.end(),greater<int>{});
//         });
//         //按照每个子数组的中位数大小降序排列
//         sort(temp_vc.begin(),temp_vc.end(),SortByMiddle<int>{});
//         //选取总数组的中位数数组
//         int tmp_size = static_cast<int>(temp_vc.size()), mid_idx = (tmp_size-1) /2;
//         auto & middle_vc = temp_vc[mid_idx];
//         int middle_idx = (static_cast<int>(middle_vc.size())-1) /2;
//         int middle_val = middle_vc[middle_idx];
//         //以中位数数组的中间元素为主元,拆分成2个数组，比主元更大的、更小的
//         vector<int> greater_vc{middle_vc.begin(),middle_vc.begin()+middle_idx},smaller_vc{middle_vc.begin()+middle_idx+1,middle_vc.end()};
//         //处理前半部分数组
//         for(i=0;i<mid_idx;++i){
//             auto & cur_vc = temp_vc[i];
//             middle_idx = (static_cast<int>(cur_vc.size()) - 1) /2;
//             //更大的是当前中位数数组下标更小的数组中下标小于等于它们各自中位数的那些值
//             greater_vc.insert(greater_vc.end(),cur_vc.begin(),cur_vc.begin()+middle_idx+1);
//             for_each(cur_vc.begin()+middle_idx+1,cur_vc.end(),[&greater_vc,&smaller_vc,middle_val](int& x){
//                 if(x >= middle_val)  
//                     greater_vc.push_back(x);
//                 else
//                     smaller_vc.push_back(x);
//             });
//         }
//         //处理后半部分数组
//         for(i=mid_idx+1;i<tmp_size;++i){
//             auto& cur_vc = temp_vc[i];
//             middle_idx = (static_cast<int>(cur_vc.size()) - 1) /2;
//             //后半部分数组的后半部分数据必定小于中位数
//             smaller_vc.insert(smaller_vc.end(),cur_vc.begin()+middle_idx,cur_vc.end());
//             for_each(cur_vc.begin(),cur_vc.begin()+middle_idx,[&greater_vc,&smaller_vc,middle_val](int& x){
//                 if(x >= middle_val)
//                     greater_vc.push_back(x);
//                 else
//                     smaller_vc.push_back(x);
//             });
//         }
//         //处理完成，比较较大数组的size与k的关系
//         //1、size = k-1，比中位数middle_value更大的只有k-1个，这个中位数整好是第k个大的数，直接返回
//         int g_size = static_cast<int>(greater_vc.size()), config = g_size - (k-1);
//         if(config == 0)
//             return middle_val;
//         //2、size > k-1,所要的值必定在前半部分,在前半部分递归查找
//         else if(config > 0)
//             return findKthLargest(greater_vc,k);
//             //size < k-1,要找的值在smaller_vc中，递归查找k-(g_size+1)个，其中+1是中位数
//         else
//             return findKthLargest(smaller_vc,k - g_size -1);
//     }
// };
//3、基于快速排序进行的筛选，每次以主元进行快排，大于主元的放到前面，小于主元的放到后面,每次就能定位1个主元位置
//以主元位置idx与k进行对比，idx==k-1,解整好为主元
//idx > k-1,解在主元的左半部分，递归查找
//idx < k-1,解在主元的右半部分，递归查找
class Solution {
    int quick_sort(vector<int> & nums,int left,int right,int k){
        if(left == right)
            return nums[left];
        //霍尔法查找主元位置，即比较数组最左端与最右端以及中间下标的中间值作为主元
        array<int,3> idx_arr{left,right,left +(right -left) /2};
        sort(idx_arr.begin(),idx_arr.end(),[&nums](const int& x,const int& y){return nums[x] < nums[y];});
        //将中间值与最开始位置进行交换
        swap(nums[left],nums[idx_arr[1]]);
        //开始快排
        int l,r,compared_val = nums[left];
        for(l=left+1,r = right;l <= r;++l,--r){
            while(l <=r && nums[l] > compared_val)
                l++;
            while(l<=r && nums[r] < compared_val)
                r--;
            if(l > r)
                break;
            swap(nums[l],nums[r]);
        }
        //放置主元
        swap(nums[left],nums[r]);
        //判断主元下标与k的关系
        int config = r-left - (k-1);
        if(config == 0)
            return compared_val;
        else if(config > 0 )
            return quick_sort(nums,left,r-1,k);
        else
            return quick_sort(nums,r+1,right,k-(r+1-left));
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        int sz =static_cast<int>(nums.size());
        return quick_sort(nums,0,sz-1,k);
    }
};

// int main(){
//     vector<int> nums{3,2,3,1,2,4,5,5,6};
//     // vector<int> nums{3,2,1,5,6,4};
//     int k=9;
//     Solution sl;
//     cout << sl.findKthLargest(nums,k) << endl;
//     return 0;
// }