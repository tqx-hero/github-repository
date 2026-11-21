/**
  3331. 修改后子树的大小
  中等
  相关标签
  premium lock icon
  相关企业
  提示
  给你一棵 n 个节点且根节点为编号 0 的树，节点编号为 0 到 n - 1 。这棵树用一个长度为 n 的数组 parent 表示，其中 parent[i] 是第 i 个节点的父亲节点的编号。由于节点 0 是根，parent[0] == -1 。

  给你一个长度为 n 的字符串 s ，其中 s[i] 是节点 i 对应的字符。

  对于节点编号从 1 到 n - 1 的每个节点 x ，我们 同时 执行以下操作 一次 ：

  找到距离节点 x 最近 的祖先节点 y ，且 s[x] == s[y] 。
  如果节点 y 不存在，那么不做任何修改。
  否则，将节点 x 与它父亲节点之间的边 删除 ，在 x 与 y 之间连接一条边，使 y 变为 x 新的父节点。
  请你返回一个长度为 n 的数组 answer ，其中 answer[i] 是 最终 树中，节点 i 为根的 子树 的 大小 。



  示例 1：

  输入：parent = [-1,0,0,1,1,1], s = "abaabc"

  输出：[6,3,1,1,1,1]

  解释：



  节点 3 的父节点从节点 1 变为节点 0 。

  示例 2：

  输入：parent = [-1,0,4,0,1], s = "abbba"

  输出：[5,2,1,1,1]

  解释：



  以下变化会同时发生：

  节点 4 的父节点从节点 1 变为节点 0 。
  节点 2 的父节点从节点 4 变为节点 1 。


  提示：

  n == parent.length == s.length
  1 <= n <= 105
  对于所有的 i >= 1 ，都有 0 <= parent[i] <= n - 1 。
  parent[0] == -1
  parent 表示一棵合法的树。
  s 只包含小写英文字母。
 */
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {

    void calculate(vector<int> &ret,unordered_map<int,vector<int>> &cache,const int idx)
    {
        if(idx == ret.size())
            return;
        //取出所有值为idx的下标，递归处理
        auto& vct = cache[idx];
        int cnt = 1;
        for(auto& num : vct)
        {
            calculate(ret,cache,num);
            cnt += ret[num];
        }
        ret[idx] = cnt;
    }

    int find_match(vector<int> &parent,string &s,vector<vector<int>> &dp,const int i,int ch)
    {
        if(i == -1)
            return -1;
        //不等于-1，判断parent是否与他相同
        if(s[i] == ch)
            return i;
        int dpval = dp[i][ch - 'a'];
        if(dpval != -2)
            return dpval;
        //如果父节点的这个值没找过，那就往上找
        //并将该值一同修改
        return  dp[i][ch - 'a'] = find_match(parent,s,dp,parent[i],ch);
    }

    public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        size_t size = parent.size();
        vector<int> ret(size,0),union_set(size);
        unordered_map<int,vector<int>> cache;
        //定义哈希表，在遍历数组时保存当前元素上级的映射值所在的下标
        vector<vector<int>> dp(size,vector<int>(26,-2));
        //从下标1开始遍历，根据parent数组查找与当前下标对应字符相等的下标
        //过程中记录下经过的不匹配的下标对应字符
        dp[0].assign(26,-1);
        int i,j;
        union_set[0] = -1;
        for(i = 1;i < size;++i)
        {
           j = find_match(parent,s,dp,parent[i],s[i]);
           dp[i][s[i] - 'a'] = j;
           if(j == -1)
               union_set[i] = parent[i];
           else 
               union_set[i] = j;
        }

        //将统计好的set按照值为key进行统计
        for(i = 1;i < size;++i)
            cache[union_set[i]].push_back(i);
        //递归计算，从下标0开始，计算每一个下标的值
        calculate(ret,cache,0);
        return ret;
    }
};

int main(){
    vector<int> parent = {-1, 0, 4, 0, 1};
    string s = "abbba";
    Solution sl;
    const auto &vct = sl.findSubtreeSizes(parent,s);
    for(int i = 0; i < vct.size() ;++i)
        cout << vct[i] << " ";
    cout << endl;
    exit(0);
}
