/**
 * 303. 区域和检索 - 数组不可变
简单
相关标签
premium lock icon
相关企业
给定一个整数数组  nums，处理以下类型的多个查询:

计算索引 left 和 right （包含 left 和 right）之间的 nums 元素的 和 ，其中 left <= right
实现 NumArray 类：

NumArray(int[] nums) 使用数组 nums 初始化对象
int sumRange(int left, int right) 返回数组 nums 中索引 left 和 right 之间的元素的 总和 ，包含 left 和 right 两点（也就是 nums[left] + nums[left + 1] + ... + nums[right] )
 

示例 1：

输入：
["NumArray", "sumRange", "sumRange", "sumRange"]
[[[-2, 0, 3, -5, 2, -1]], [0, 2], [2, 5], [0, 5]]
输出：
[null, 1, -1, -3]

解释：
NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1)) 
numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1))
 

提示：

1 <= nums.length <= 104
-105 <= nums[i] <= 105
0 <= left <= right < nums.length
最多调用 104 次 sumRange 方法
 */
#include <vector>
#include <iostream>
using namespace std;

class NumArray {
    vector<int> prefix;
public:
    NumArray(vector<int>& nums) {
        int size = static_cast<int>(nums.size()),i;
        prefix.resize(size+1);
        prefix[0] = 0;
        for(i=1;i<size+1;++i)
            prefix[i] =prefix[i-1]+nums[i-1];
    }
    
    int sumRange(int left, int right) {
        return prefix[right+1] - prefix[left];   
    }
};

// int main(){
//     /* NumArray numArray = new NumArray([-2, 0, 3, -5, 2, -1]);
// numArray.sumRange(0, 2); // return 1 ((-2) + 0 + 3)
// numArray.sumRange(2, 5); // return -1 (3 + (-5) + 2 + (-1)) 
// numArray.sumRange(0, 5); // return -3 ((-2) + 0 + 3 + (-5) + 2 + (-1)) */
//     NumArray na(vector<int>{-2, 0, 3, -5, 2, -1});
//     cout << na.sumRange(0,2) << endl;
//     cout << na.sumRange(2,5) << endl;
//     cout << na.sumRange(0,5) << endl;
//     return 0;
// }