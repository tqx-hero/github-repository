//
// Created by Administrator on 2026/7/20.
//
#include <iostream>
using namespace std;

void others();

namespace n1 {
    int x = 1;
}

namespace n2 {
    int x = 2;
}

// int main() {
//     using namespace n1;
//     cout << x << endl; //1
//     {
//         int x = 4;
//         cout << x << "," << n1::x << "," << n2::x << endl; //4,1,2
//     }
//     using n2::x;
//     cout << x << endl; //2
//     others();
//     return 0;
// }

void others() {
    using namespace n2;
    cout << x << endl; //2
    {
        int x = 4;
        cout << x << "," << n1::x << "," << n2::x << endl; //4,1,2
    }
    using n2::x;
    cout << x << endl; //2
}
