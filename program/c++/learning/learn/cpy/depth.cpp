//
// Created by Administrator on 2026/7/10.
//

#include <cstdlib>
#include <cstring>
#include <iostream>

class Teacher {
    char *name;
    int age;

public:
    Teacher(const char *name, int age)
        : age(age) {
        this->name = (char *) malloc(strlen(name) + 1);
        strcpy(this->name, name);
    }

    [[nodiscard]] char *name1() const {
        return name;
    }

    [[nodiscard]] int age1() const {
        return age;
    }

    //成员变量有指针类型，必须先给指针开辟内存空间，生成一个新的指针，然后将被拷贝对象的指针指向的数据复制一份
    //然后赋给这个新指针,否则会出现析构时free同一块内存空间2次的问题
    Teacher(const Teacher &teacher) : age(teacher.age) {
        //指针必须进行深拷贝
        this->name = (char *) malloc(strlen(teacher.name) + 1);
        strcpy(this->name, teacher.name);
    }

    ~Teacher() {
        free(this->name);
        this->name = nullptr;
    }
};

void print() {
    Teacher t1{"张三", 20};
    std::cout << t1.name1() << ":" << t1.age1() << std::endl;
    //调用默认拷贝构造，成员变量如果有指针或者引用，会直接复制并赋值
    //当调用析构函数时，由于2个对象使用的同一个指针
    //会free一个指针2次，抛出异常,所以如果有指针，必须显式给出拷贝构造并手动给指针开辟空间，然后复制指针
    Teacher t2(t1);
}

// int main() {
//     print();
//     return 0;
// }
