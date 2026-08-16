//
// Created by Administrator on 2026/7/7.
//
#include <complex>
#include <iomanip>
#include <vector>
#include <iostream>
using namespace std;

vector<string> splitString(string &s, string &t) {
    vector<string> result;
    if (s.empty())
        return result;
    size_t start = 0, pos, sub_len = t.length(), s_len = s.size();
    //如果子串存在于字符串，返回下标
    while ((pos = s.find(t, start)) != string::npos) {
        result.push_back(s.substr(start, pos - start));
        start = pos + sub_len;
    }
    if (start != s_len - 1)
        result.push_back(s.substr(start, s_len - start));
    return result;
}
#define PI (3.14)
// int main() {
//     //asdf,Hello,ok
//     // ,
//     // string s("asdf,Hello,ok"), t(",");
//     // vector<string> result = splitString(s, t);
//     // for (string &str: result)
//     //     cout << str << endl;
//     // double r = 233;
//     // cout << pow(r,2) * PI <<endl;
//     // cout << fixed << setprecision(2) << pow(r,2) * PI << endl;
//     return 0;
// }
