/**
832. 翻转图像
简单
相关标签
premium lock icon
相关企业
给定一个 n x n 的二进制矩阵 image ，先 水平 翻转图像，然后 反转 图像并返回 结果 。

水平翻转图片就是将图片的每一行都进行翻转，即逆序。

例如，水平翻转 [1,1,0] 的结果是 [0,1,1]。
反转图片的意思是图片中的 0 全部被 1 替换， 1 全部被 0 替换。

例如，反转 [0,1,1] 的结果是 [1,0,0]。
 

示例 1：

输入：image = [[1,1,0],[1,0,1],[0,0,0]]
输出：[[1,0,0],[0,1,0],[1,1,1]]
解释：首先翻转每一行: [[0,1,1],[1,0,1],[0,0,0]]；
     然后反转图片: [[1,0,0],[0,1,0],[1,1,1]]
示例 2：

输入：image = [[1,1,0,0],[1,0,0,1],[0,1,1,1],[1,0,1,0]]
输出：[[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
解释：首先翻转每一行: [[0,0,1,1],[1,0,0,1],[1,1,1,0],[0,1,0,1]]；
     然后反转图片: [[1,1,0,0],[0,1,1,0],[0,0,0,1],[1,0,1,0]]
 

提示：

n == image.length
n == image[i].length
1 <= n <= 20
images[i][j] == 0 或 1.
  */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& image) {
	size_t row = image.size(),col = image[0].size();
	int i,left,right;
	for(i = 0;i < row;++i){
	    for(left = 0,right = col - 1;left < right;++left,--right){
		int temp = image[i][left] ^ 0x01;
		image[i][left] = image[i][right] ^ 0x01;
		image[i][right] = temp;
	    }
	    if(left == right)
		image[i][left] ^= 0x01;
	}
	return image;
    }
};

int main(){
    vector<vector<int>> image{
vector<int>{1,1,0},vector<int>{1,0,1},vector<int>{0,0,0}
    };
    Solution sl;
    const auto& vc = sl.flipAndInvertImage(image);
    for_each(vc.begin(),vc.end(),[](const vector<int> &v){
	    	for_each(v.begin(),v.end(),[](const int x){cout << x << " ";});
		cout << endl;
	    });
    return 0;
}
