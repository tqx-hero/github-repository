/**
 * 169. 多数元素
已解答
简单
相关标签
premium lock icon
相关企业
给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数 大于 ⌊ n/2 ⌋ 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

 

示例 1：

输入：nums = [3,2,3]
输出：3
示例 2：

输入：nums = [2,2,1,1,1,2,2]
输出：2
 

提示：
n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
输入保证数组中一定有一个多数元素。
 

进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。
 */
#include <vector>
#include <iostream>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int size =static_cast<int>(nums.size()), cnt = 1,value = nums[0];
        for(int i=1;i<size;++i){
            if(nums[i] == value)
                cnt++;
            else if(cnt)
                cnt--;
            else{
                value = nums[i];
                cnt = 1;
            }
        }
        return value;
    }
};

int main(){
    vector<int> nums{2,2,1,1,1,2,2};
    Solution sl;
    cout << sl.majorityElement(nums) << endl;
    return 0;
}