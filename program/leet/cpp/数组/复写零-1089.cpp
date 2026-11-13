#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution {
    public:
        void duplicateZeros(vector<int>& arr) {
            queue<int> temp_arr;
            size_t sz = arr.size();
            for(auto& num : arr){
                if(temp_arr.size() >= sz)
                    break;
                if(num == 0){
                    temp_arr.push(0);
                    temp_arr.push(0);
                }else
                    temp_arr.push(num);
            }
            for(auto& num : arr){
                num = temp_arr.front();
                temp_arr.pop();
            }
        }
};

int main(){
    vector<int> arr{1,0,2,3,0,4,5,0};
    Solution sl;
    sl.duplicateZeros(arr);
    for(int i = 0;i < arr.size();++i)
        cout << arr[i] << endl;
    return 0;
}
