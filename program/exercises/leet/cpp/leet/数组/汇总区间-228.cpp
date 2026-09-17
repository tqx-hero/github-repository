/**
 * 228. 汇总区间
简单
相关标签
premium lock icon
相关企业
给定一个  无重复元素 的 有序 整数数组 nums 。

区间 [a,b] 是从 a 到 b（包含）的所有整数的集合。

返回 恰好覆盖数组中所有数字 的 最小有序 区间范围列表 。也就是说，nums 的每个元素都恰好被某个区间范围所覆盖，并且不存在属于某个区间但不属于 nums 的数字 x 。

列表中的每个区间范围 [a,b] 应该按如下格式输出：

"a->b" ，如果 a != b
"a" ，如果 a == b
 

示例 1：

输入：nums = [0,1,2,4,5,7]
输出：["0->2","4->5","7"]
解释：区间范围是：
[0,2] --> "0->2"
[4,5] --> "4->5"
[7,7] --> "7"
示例 2：

输入：nums = [0,2,3,4,6,8,9]
输出：["0","2->4","6","8->9"]
解释：区间范围是：
[0,0] --> "0"
[2,4] --> "2->4"
[6,6] --> "6"
[8,9] --> "8->9"
 

提示：

0 <= nums.length <= 20
-231 <= nums[i] <= 231 - 1
nums 中的所有值都 互不相同
nums 按升序排列
 */
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution {
    string build_str(int begin_num,int end_num){
        string str = to_string(begin_num);
        if(end_num != begin_num){
            str += "->";
            str += to_string(end_num);
        }
        return str;
    }
public:
    vector<string> summaryRanges(vector<int>& nums) {
        vector<string> ret;
        int size;
        if(!(size =static_cast<int>(nums.size())))
            return ret;
        int begin_num = nums[0],end_num = begin_num,i;
        for(i=1;i<size;++i){
            if(nums[i] == nums[i-1]+1)
                end_num++;
            else{
                //如果数值不连续，统计当前为止的字符序列
                ret.push_back(build_str(begin_num,end_num));
                begin_num = end_num = nums[i];
            }
        }
        ret.push_back(build_str(begin_num,end_num));
        return ret;
    }
};

// int main(){
//     // vector<int> nums = {0,1,2,4,5,7};
//     vector<int> nums = {-1};
//     Solution sl;
//     const auto& vec = sl.summaryRanges(nums);
//     for_each(vec.begin(),vec.end(),[](const string& str){ cout << str << " ";});
//     cout << endl;
//     return 0;
// }