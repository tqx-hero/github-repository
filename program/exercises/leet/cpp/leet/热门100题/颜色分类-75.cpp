/**
 * 75. 颜色分类
中等
相关标签
premium lock icon
相关企业
提示
给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums ，原地 对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

必须在不使用库内置的 sort 函数的情况下解决这个问题。

 

示例 1：

输入：nums = [2,0,2,1,1,0]

输出：[0,0,1,1,2,2]

解释：

该数组包含两个 0、两个 1 和两个 2。将它们原地排序后，所有 0 排在最前面，接着是所有 1，最后是所有 2。

示例 2：

输入：nums = [2,0,1]

输出：[0,1,2]

解释：

数组中有且仅有一个 0、一个 1 和一个 2，按 0、1、2 的顺序原地排列。

 

提示：

n == nums.length
1 <= n <= 300
nums[i] 为 0、1 或 2
 

进阶：

你能想出一个仅使用常数空间的一趟扫描算法吗？
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int size =static_cast<int>(nums.size()), zero_cnt =0,one_count = 0 ;
        for(int num : nums){
            if(num == 0)
                zero_cnt++;
            else if(num ==1)
                one_count++;
        }
        int i;
        for(i=0;zero_cnt;i++,zero_cnt--)
            nums[i] =0;
        for(;one_count;++i,--one_count)
            nums[i] =1;
        for(;i<size;++i)
            nums[i] = 2;
    }
};

int main(){
    vector<int> nums{2,0,2,1,1,0};
    Solution sl;
    sl.sortColors(nums);
    for_each(nums.begin(),nums.end(),[](const int x){ cout << x << " ";});
    return 0;
}