#include <iostream>
#include <cmath>
using namespace std;
//判断一个数是不是质数
//1、是否小于等于1，是则不是质数
//2、是否等于2，是则是质数
//3、是否是偶数，是则不是
//4、开方求出它的算术平方根向下取整的整数x，然后从3~x所有的奇数依次查看
//是否能被这个数整除，如果可以，则不是
bool is_integer(double num);

bool is_prime(int num);

//int main() {
//	cout << "请输入:" << endl;
//	int num;
//	cin >> num;
//	bool flag =  is_prime(num);
//	cout << "输入的数是否为质数: " << flag <<endl;
//	return 0;
//}

bool is_prime(int num) {
    if (num <= 1)
        return false;
    if (num == 2)
        return true;
    //如果为偶数，肯定不是质数
    if (!(num & 0x1))
        return false;
    //开方
    double res = sqrt(num), nums = (double) num;
    //查看平方根是否为整数，是则不是质数
    if (is_integer(res))
        return false;
    int n = (int) res;
    for (int i = 3; i <= n; i += 2) {
        if (is_integer(nums / i))
            return false;
    }
    return true;
}

bool is_integer(double num) {
    int tmp = (int) num;
    return num == (double) tmp;
}
