/**
  1128. 等价多米诺骨牌对的数量
  简单
  相关标签
  premium lock icon
  相关企业
  提示
  给你一组多米诺骨牌 dominoes 。

  形式上，dominoes[i] = [a, b] 与 dominoes[j] = [c, d] 等价 当且仅当 (a == c 且 b == d) 或者 (a == d 且 b == c) 。即一张骨牌可以通过旋转 0 度或 180 度得到另一张多米诺骨牌。

  在 0 <= i < j < dominoes.length 的前提下，找出满足 dominoes[i] 和 dominoes[j] 等价的骨牌对 (i, j) 的数量。



  示例 1：

  输入：dominoes = [[1,2],[2,1],[3,4],[5,6]]
  输出：1
  示例 2：

  输入：dominoes = [[1,2],[1,2],[1,1],[1,2],[2,2]]
  输出：3


  提示：

  1 <= dominoes.length <= 4 * 104
  dominoes[i].length == 2
  1 <= dominoes[i][j] <= 9
 */
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
namespace Hash_self{
    template <typename T>
        void hash_combine(size_t& seed, const T& val) {
            seed ^= std::hash<T>{}(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
}
class Solution {
    struct TPair{
        int x,y;

        TPair(int x,int y) : x(x),y(y){};

        bool operator== (const TPair & other) const{
            return x == other.x && y == other.y;
        }
    };

    struct TPHash {
        size_t operator()(const TPair& pr) const{
            size_t seed = 0;
            Hash_self::hash_combine(seed,pr.x);
            Hash_self::hash_combine(seed,pr.y);
            return seed;
        }
    };

    public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        int ret = 0;
        unordered_map<TPair,int,TPHash> cache;
        for(auto& vct : dominoes){
            int min = vct[0],max = vct[1];
            if(min > max)
                swap(min,max);
            cache[{min,max}]++;
        }
        for(auto& pair : cache){
            int count = pair.second;
            if(count > 1)
                ret += (count - 1) * count / 2;
        }
        return ret;
    }
};

int main(){
    //dominoes = [[1,2],[2,1],[3,4],[5,6]]
    vector<vector<int>> dominoes{
        vector<int>{1,2},
            vector<int>{2,1},
            vector<int>{3,4},
            vector<int>{5,6}
    };
    Solution sl;
    cout << sl.numEquivDominoPairs(dominoes) << endl;
    return 0;
}
