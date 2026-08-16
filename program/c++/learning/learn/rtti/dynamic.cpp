//
// Created by Administrator on 2026/7/22.
//
#include <iostream>

namespace rtti {
    class Dyn {
    protected:
        virtual  ~Dyn() = default;
    };

    class CDyn : public Dyn {
    };
}

// int main() {
//     using namespace rtti;
//     CDyn c;
//     Dyn *dp = &c;
//     CDyn * cp=&c;
//     //dynamic_cast类型转化必须要有多态性，也就是说基类必须要有虚函数
//     //否则类型转换编译器不通过
//     std::cout << dynamic_cast<CDyn *>(dp) << std::endl;
//     //static_cast则不需要必须有虚函数，即没有多态性限制，可以自由地进行父子类间转换，以及基本数据类型间转换，但是没有安全检查
//     std::cout << static_cast<CDyn *>(dp) << std::endl;
//     std::cout << dynamic_cast<Dyn *>(cp) << std::endl;
//     return 0;
// }
