//
// Created by Administrator on 2026/7/17.
//
#include <iostream>

class Building {
};

class Animal {
public:
    virtual  ~Animal(){}
};

class Cat : public Animal {
};
//static_cast使用
void testStaticCast() {
    int a = 65535;
    //static_cast可以进行基础数据类型之间的转换
    auto c = static_cast<unsigned short>(a);
    std::cout << c << std::endl;

    //对于指针类型
    //基本数据类型指针不能使用static_cast
    // int *ap =nullptr;
    // char * cp =static_cast<char*> (ap);
    //对于对象指针，同样不能使用static_cast
    // Building *building = nullptr;
    // Animal* animal = static_cast<Animal *> (building);

    //但是对于子类父类指针的转换，可以使用static_cast
    // Cat *cat = nullptr;
    // Animal *animal = static_cast<Animal *>(cat);
    // cat = static_cast<Cat *>(animal);

    //对于拥有继承关系的子父类之间的引用，static_cast同样可以进行转换
    Animal an;
    Animal & anObj = an;
    Cat& catObj = static_cast<Cat &>(anObj);
    anObj = static_cast<Animal &> (catObj);
}

//dynamic_cast使用
void testDynamicCast() {
    //不能转换基本数据类型
    // int a = 10;
    // char c = dynamic_cast<char> (a); //编译报错
    //不能进行没有继承关系的两个对象指针之间的转换,引用同样如此
    // Building* building=nullptr;
    // Animal* animal =dynamic_cast<Animal *>(building);

    //父类必须有至少一个虚函数，才可以使用,即父类中的函数必须具有多态性，才可以向下转型
    Animal* animal= nullptr;
    Cat* cat = dynamic_cast<Cat *>(animal);  //编译报错

    //向上转型是绝对安全的，子类 -->父类，属于是大空间转小空间，内存超出的部分直接截断，也不会出现内存访问越界的风险。
    //所以这样是可以用dynamic_cast,但是向上转型隐式类型转换就可以做到，且没有运行时开销
    // Cat * cat =nullptr;
    // Animal* animal = dynamic_cast<Animal *> (cat);

}
//const_cast：给指针或者引用添加或者取消const属性
void testConstCast() {
    //给指针或者引用取消const属性
    const int& a =20;
    auto nca = const_cast<int&> (a);
    nca = 10;
    //给指针或引用添加const属性
    Animal* animal1=nullptr;
    const Animal* animal2 = const_cast<const Animal*>(animal1);
}
//reinterpret_cast,强制类型转换，直接把源对象类型转换为目标对象类型
void testReinterpretCast() {
    const int & a =20;
    const char& ch =  reinterpret_cast<const char&>(a);

    Building * building=nullptr;
    Animal* animal = reinterpret_cast<Animal *> (building);
    void* vdptr = reinterpret_cast<void*> (animal);
}

// int main() {

//     return 0;
// }
