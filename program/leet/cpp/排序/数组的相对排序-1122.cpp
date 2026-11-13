/**
  1122. 数组的相对排序
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给你两个数组，arr1 和 arr2，arr2 中的元素各不相同，arr2 中的每个元素都出现在 arr1 中。

  对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在 arr2 中出现过的元素需要按照升序放在 arr1 的末尾。



  示例 1：

  输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
  输出：[2,2,2,1,4,3,3,9,6,7,19]
  示例  2:

  输入：arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
  输出：[22,28,8,6,17,44]


  提示：

  1 <= arr1.length, arr2.length <= 1000
  0 <= arr1[i], arr2[i] <= 1000
  arr2 中的元素 arr2[i]  各不相同 
  arr2 中的每个元素 arr2[i] 都出现在 arr1 中
 **/
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution {
    public:
        vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
            vector<int> ret(arr1.size());
            unordered_map<int,int> cache;
            for(auto & num :arr1)
                cache[num]++;
            int i,j;
            for(i = 0,j = 0;j < arr2.size();++j){
                int num = arr2[j];
                while(cache[num]--)
                    ret[i++] = num;
                cache.erase(num);
            }
            //将哈希表中仍然存在的值放入ret
            j = i;
            for(auto &pair : cache){
                int count = pair.second,num = pair.first;
                while(count--)
                    ret[i++] = pair.first;
            }
            sort(ret.begin() + j,ret.end());
            return ret;
        }
};

int main(){
    vector<int> arr1{2,3,1,3,2,4,6,7,9,2,19}, arr2{2,1,4,3,9,6};
    Solution sl;
    const auto& vc = sl.relativeSortArray(arr1,arr2);
    for(int i =0;i < vc.size();++i){
        cout << vc[i] << " ";
    }
    cout << endl;
    return 0;
}
