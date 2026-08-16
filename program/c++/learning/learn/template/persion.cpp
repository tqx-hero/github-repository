//
// Created by Administrator on 2026/7/16.
//
#include <iostream>
#include <string>

//template<typename T, typename K>
//class Persion {
//public:
//    //声明友元函数，只要参数是模板类，之前必须声明template
//    //正常情况下，友元函数还是尽量少用，它破坏了对象的封装特性
//    template<typename T, typename K>
//    friend void print(const Persion<T, K> &p);
//    template<typename T, typename K>
//    friend std::ostream& operator<<(std::ostream& os, const Persion<T, K>& persion);
//    Persion(T name, K age) : name(name), age(age) {
//    }
//
//    T getName() const{
//        return this->name;
//    }
//
//    K getAge() const{
//        return this->age;
//    }
//
//    void print() {
//        using namespace std;
//        cout << this->name << endl;
//        cout << this->age << endl;
//    }
//
//private:
//    T name;
//    K age;
//};
////每次使用模板类，都必须在使用之前声明template
//template<typename T, typename K>
//void print(const Persion<T, K> &p) {
//    using namespace std;
//    cout << p.name << endl;
//    cout << p.age << endl;
//}
//
//template<class T,class K>
//std::ostream& operator<<(std::ostream& os,const Persion<T,K>& persion) {
//    os << persion.getName() << std::endl;
//    os << persion.getAge();
//    return os;
//}
//
//int main() {
//    Persion<std::string, int> pn("张三", 20);
//    // pn.print();
//    //print(pn);
//    std::cout << pn << std::endl;
//    return 0;
//}
