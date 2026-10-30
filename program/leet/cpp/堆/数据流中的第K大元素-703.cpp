/**
 *703. 数据流中的第 K 大元素
简单
相关标签
premium lock icon
相关企业
设计一个找到数据流中第 k 大元素的类（class）。注意是排序后的第 k 大元素，不是第 k 个不同的元素。

请实现 KthLargest 类：

KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。
 

示例 1：

输入：
["KthLargest", "add", "add", "add", "add", "add"]
[[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]

输出：[null, 4, 5, 5, 8, 8]

解释：

KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
kthLargest.add(3); // 返回 4
kthLargest.add(5); // 返回 5
kthLargest.add(10); // 返回 5
kthLargest.add(9); // 返回 8
kthLargest.add(4); // 返回 8

 

示例 2：

输入：
["KthLargest", "add", "add", "add", "add"]
[[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]

输出：[null, 7, 7, 7, 8]

解释：

KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
kthLargest.add(2); // 返回 7
kthLargest.add(10); // 返回 7
kthLargest.add(9); // 返回 7
kthLargest.add(9); // 返回 8
 

提示：
0 <= nums.length <= 104
1 <= k <= nums.length + 1
-104 <= nums[i] <= 104
-104 <= val <= 104
最多调用 add 方法 104 次
 */
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

class KthLargest {
	int knum;
	priority_queue<int,vector<int>,greater<int>> minheap;
public:
    KthLargest(int k, vector<int>& nums) : knum(k) {
	    size_t sz = nums.size();
	    if(sz == 0)
		    return;
	    std::sort(nums.begin(),nums.end(),std::greater<int>());
	    //第一种，使用swap交换两个堆的空间
	    priority_queue<int,vector<int>,greater<int>> tmpheap{nums.begin(),nums.begin() + std::min(k,static_cast<int>(sz))};
	    minheap.swap(tmpheap);
	    //第二种，使用move函数，直接将nums的k个元素放到数组，但是优先队列没有迭代器，所以不支持
	    //std::move(nums.begin(),nums.begin() + std::min(k,static_cast<int>(sz)),minheap.begin());
    }

    int add(int val) {
	    if(minheap.size() < knum)
		    minheap.push(val);
	    //比较val与堆顶的大小
	    else if(val > minheap.top()){
		    minheap.pop();
		    minheap.push(val);
	    }
	    return minheap.top();
    }
};

int main(){
	vector<int> nums{4,5,8,2};
	KthLargest kthLargest{3, nums};
	cout << kthLargest.add(3) << endl; // 返回 4
	cout << kthLargest.add(5) << endl; // 返回 5
	cout << kthLargest.add(10) << endl; // 返回 5
	cout << kthLargest.add(9) << endl; // 返回 8
	cout << kthLargest.add(4) << endl; // 返回 8
	return 0;
}
