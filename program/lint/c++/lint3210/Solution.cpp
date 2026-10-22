//
// Created by Administrator on 2026/7/7.
//
#include <iostream>
#include <vector>
using namespace std;

bool train(vector<int> &in_order, vector<int> &leave_order) {
    vector<int> stack;
    int i, j;
    int inSize = (int) in_order.size(), outSize = (int) leave_order.size();
    j = 0;
    for (i = 0; i < inSize && j < outSize; i++) {
        stack.push_back(in_order.at(i));
        while (!stack.empty()) {
            int top = stack.back();
            //如果栈顶等于出站的当前元素，弹栈
            //j指针前移
            if (top == leave_order.at(j)) {
                stack.pop_back();
                j++;
            } else
                break;
        }
    }
    return stack.empty();
}

int main() {
    //[1,2,3]
    // [3,1,2]
    vector<int> in{1, 2, 3}, out{3, 1, 2};
    // vector<int> in{1, 2, 3}, out{1, 3, 2};
    bool flag = train(in, out);
    cout << flag << endl;
    return 0;
}
