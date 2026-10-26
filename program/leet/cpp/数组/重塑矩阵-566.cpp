#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
	size_t row = mat.size(),col = mat[0].size();
	if(row * col != r * c)
		return mat;
	vector<vector<int>> ret(r,vector<int>(c));
	int i = 0,j = 0;
	for_each(mat.begin(),mat.end(),[&i,&j,&ret,c](const vector<int> &vc){
		for_each(vc.begin(),vc.end(),[&i,&j,&ret,c](const int x){
			if(j >= c){
				j= 0;
				i++;
			}
			ret[i][j] = x;
			j++;
		});
	});
	return ret;
    }
};

int main(){
	//mat = [[1,2],[3,4]], r = 1, c = 4
	vector<vector<int>> mat{vector<int>{1,2},vector<int>{3,4}};
	int r=1,c=4;
	Solution sl;
	const auto& vc = sl.matrixReshape(mat,r,c);
	for_each(vc.begin(),vc.end(),[](const vector<int>& v){
		for_each(v.begin(),v.end(),[](const int x){
			cout << x << " ";
		});
		cout << endl;
	});
	return 0;
}
