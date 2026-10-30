/**
 *766. 托普利茨矩阵
简单
相关标签
premium lock icon
相关企业
提示
给你一个 m x n 的矩阵 matrix 。如果这个矩阵是托普利茨矩阵，返回 true ；否则，返回 false 。

如果矩阵上每一条由左上到右下的对角线上的元素都相同，那么这个矩阵是 托普利茨矩阵 。

 

示例 1：


输入：matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
输出：true
解释：
在上述矩阵中, 其对角线为: 
"[9]", "[5, 5]", "[1, 1, 1]", "[2, 2, 2]", "[3, 3]", "[4]"。 
各条对角线上的所有元素均相同, 因此答案是 True 。
示例 2：


输入：matrix = [[1,2],[2,2]]
输出：false
解释：
对角线 "[1, 2]" 上的元素不同。
 

提示：

m == matrix.length
n == matrix[i].length
1 <= m, n <= 20
0 <= matrix[i][j] <= 99
 

进阶：

如果矩阵存储在磁盘上，并且内存有限，以至于一次最多只能将矩阵的一行加载到内存中，该怎么办？
如果矩阵太大，以至于一次只能将不完整的一行加载到内存中，该怎么办？
 */
#include <vector>
#include <iostream>
using namespace std;

#define LOOP(__X,__Y) int x = __X,y = __Y; \
		      while(isvalid(x,y)){ \
			if(matrix[x][y] != num) \
			    return false; \
			x++; \
			y++; \
		      }
class Solution {
    size_t row,col;
    bool isvalid(int x,int y){
	if(x < 0 || x >=row || y < 0 || y >= col)
	    return false;
	return true;
    }
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
	//第一行与第一列遍历
	row = matrix.size();
	col = matrix[0].size();
	//遍历第一行
	int j;
	for(j = 0;j < col - 1;++j){
	    int num = matrix[0][j];//获取num，后续比对用
	    LOOP(1,j+1)
	}
	//遍历第一列
	for(j = 1;j < row - 1;++j){
	    int num = matrix[j][0];
	    LOOP(j+1,1)
	}
	return true;
    }
};

int main(){
    //matrix = [[1,2,3,4],[5,1,2,3],[9,5,1,2]]
    vector<vector<int>> matrix{
	vector<int>{1,2,3,4},
	vector<int>{5,1,2,3},
	vector<int>{9,5,1,2}
    };
    Solution sl;
    cout << sl.isToeplitzMatrix(matrix) << endl;
    return 0;
}
