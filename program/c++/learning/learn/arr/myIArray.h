//
// Created by Administrator on 2026/7/11.
//

#ifndef LN_MyIArray_H
#define LN_MyIArray_H
#define MY_ARRAY_DEFAULT_CAPACITY 64

//自定义数组类
class MyIArray {
    //总大小
    int size;
    int *arrayPtr;

public:
    MyIArray(int);

    ~MyIArray();

    const int length() const;

    MyIArray(const MyIArray &);

    MyIArray &operator=(const MyIArray &);

    //重载操作符[]
    int &operator[](int);

    //重载操作符[]，供被const修饰的类对象调用，保证const对象的数据不会被修改，确保const的语义正确
    const int &operator[](int) const;

    //重载运算符==，用于判断2个对象的值是否相同
    bool operator==(const MyIArray &) const;

    bool operator!=(const MyIArray &) const;
};
#endif //LN_MyIArray_H
