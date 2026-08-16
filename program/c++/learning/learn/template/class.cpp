//
// Created by Administrator on 2026/7/16.
//
#if 0
#include <iostream>
template<typename T, typename W>
class Bus {
public:
    Bus(const T &age, const W &name)
        : age(age),
          name(name) {
    }

    explicit Bus(const T &age)
        : age(age), name("") {
    }

    void show() {
        using namespace std;
        cout << this->age << endl;
        cout << this->name << endl;
    }

private:
    T age;
    W name;
};
#endif

// int main() {
//     Bus<int, std::string> bs(20.0f, "张三"), as(10);
//     bs.show();
//     as.show();
//     return 0;
// }
