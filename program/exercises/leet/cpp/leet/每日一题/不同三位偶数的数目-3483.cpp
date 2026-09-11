/**
 * 3483. 不同三位偶数的数目
简单
相关标签
premium lock icon
相关企业
提示
给你一个数字数组 digits，你需要从中选择三个数字组成一个三位偶数，你的任务是求出 不同 三位偶数的数量。

注意：每个数字在三位偶数中都只能使用 一次 ，并且 不能 有前导零。

 

示例 1：

输入： digits = [1,2,3,4]

输出： 12

解释： 可以形成的 12 个不同的三位偶数是 124，132，134，142，214，234，312，314，324，342，412 和 432。注意，不能形成 222，因为数字 2 只有一个。

示例 2：

输入： digits = [0,2,2]

输出： 2

解释： 可以形成的三位偶数是 202 和 220。注意，数字 2 可以使用两次，因为数组中有两个 2 。

示例 3：

输入： digits = [6,6,6]

输出： 1

解释： 只能形成 666。

示例 4：

输入： digits = [1,3,5]

输出： 0

解释： 无法形成三位偶数。

 

提示：

3 <= digits.length <= 10
0 <= digits[i] <= 9
 */
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;
//1、先统计数字在数组中出现的次数
//2、因为要组成3位数的偶数，那就需要个位为0/2/4/6/8这几个数，十位百位在剩余的数中两两组合,并且需要特殊注意0不能在百位
//3、先选中存在的一个偶数作为个位，两两组合时，百位刨除0，在其余剩余的数字中选择一位，十位数字在包含0的基础上在剩余数字中选择一个
class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        //统计数字出现的次数
        //按照奇偶分成2个哈希表，便于后面按照个位是偶数位进行统计
        unordered_map<int,int> odd_map,even_map;
        for(int num : digits){
            if(num % 2 == 1)
                odd_map[num]++;
            else 
                even_map[num]++;
        }
        //查看有无偶数，没有偶数直接返回
        if(even_map.empty())
            return 0;
        //查看有无0,并统计0的个数
        unordered_map<int,int>::iterator it,end_it = even_map.end();
        int zero_cnt = (it = even_map.find(0)) == end_it ?  0 : it->second;
        //需要统计其余值超过1个数量的个数
        int more_count = 0,i,
        //统计非0的元素个数
        total_count = static_cast<int>(odd_map.size()) + static_cast<int>(even_map.size()) -(zero_cnt ? 1 : 0 );
        for(i=1;i<10;i+=2)
            if((it = odd_map.find(i)) !=end_it && it->second > 1)
                more_count++;
        for(i = 2;i<10;i+=2)
            if((it = even_map.find(i)) !=end_it && it->second > 1)
                more_count++;
        int ret =0;
        //遍历偶数的哈希表,以当前元素为个位，其余数值进行排列组合
        for(auto& pr: even_map){
            //该偶数为个位，计数-1
            int value = pr.first,cnt =pr.second - 1;
            int third,ten;
            //当前偶数为0时，百位有total_count种选择
            if(value == 0){
                third = total_count;
                //十位有百位选择-1+(还有无0)种选择(不考虑重复情况下)
                //如果减去1个0还有0，那就+1
                ten = third -1  + (cnt ? 1 : 0);
                //不重复的排列组合就是十位*百位
                //重复的排列组合就是之前统计的more_count的个数,也就是非0的个数大于1个的元素个数
                ret += third * ten + more_count;
            }
            else{
                //当前值不为0，百位就是total_count - 1 + 还有没有剩余的当前值,有就在+1种情况
                third = total_count - 1 + (cnt ? 1 : 0);
                //十位数选择是百位-1，当然如果有0，那就再+1种
                ten = third -1 + (zero_cnt ? 1 : 0);
                //结果就是十位种数*百位种数+重复数字的个数。
                //当然如果当前值的数字等于1个，表明统计之前个数有2个，more_count多统计了一次，那就需要在more_count减去1
                ret += third * ten + (more_count ? 
                                                (more_count - (cnt == 1 ? 1 : 0))
                                                : 0);
            }
        }
        return ret;
    }
};

// int main(){
//     // vector<int> digits{1,2,3,4};
//     // vector<int> digits{3,1,5};
//     vector<int> digits{3,3,2};
//     // vector<int> digits{6,6,6};
//     // vector<int> digits{2,2,0};
//     Solution sl;
//     cout << sl.totalNumbers(digits) << endl;
//     return 0;
// }