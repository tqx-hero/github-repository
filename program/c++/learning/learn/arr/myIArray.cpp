//
// Created by Administrator on 2026/7/11.
//
//自定义数组类
#include "MyIArray.h"
#include <cstring>
#include <iostream>
using namespace std;
MyIArray::MyIArray(int size)
    : size(size <= 0 ? MY_ARRAY_DEFAULT_CAPACITY : size) {
    arrayPtr = new int[this->size];
}

MyIArray::~MyIArray() {
    delete[] arrayPtr;
    arrayPtr = nullptr;
}

const int MyIArray::length() const {
    return this->size;
}

MyIArray::MyIArray(const MyIArray &ann) : size(ann.size) {
    arrayPtr = new int[size];
    memcpy(arrayPtr, ann.arrayPtr, size * sizeof(int));
}

MyIArray &MyIArray::operator=(const MyIArray &ann) {
    //先判断是否是同一个对象
    if (this == &ann)
        return *this;
    //释放this本身的指针指向的内存
    delete[] arrayPtr;
    this->size = ann.size;
    arrayPtr = new int[this->size];
    memcpy(arrayPtr, ann.arrayPtr, this->size * sizeof(int));
    return *this;
}

//重载操作符[]
int &MyIArray::operator[](int offset) {
    if (offset < 0 || offset >= size)
        return this->arrayPtr[0];
    return this->arrayPtr[offset];
}

bool MyIArray::operator!=(const MyIArray &ann) const {
    return !(*this == ann);
}

bool MyIArray::operator==(const MyIArray &ann) const {
    if (this == &ann)
        return true;
    int len;
    const MyIArray &cur = *this;
    if ((len = cur.length()) != ann.length())
        return false;
    for (int i = 0; i < len; i++)
        if (cur[i] != ann[i])
            return false;
    return true;
}


const int &MyIArray::operator[](int offset) const {
    if (offset < 0 || offset >= size)
        return this->arrayPtr[0];
    return this->arrayPtr[offset];
}


//重载标准输出流运算符 <<,但是如果没声明MyIArray为const类型，函数内可对它进行修改
//违背了面向对象的基本准则，即对象的属性外部可以直接修改而不用通过类
//所以需要对它添加const保证不会对类进行修改
// ostream &operator<<(ostream &os, MyIArray &arr) {
//     int size = arr.length();
//     for (int i = 0; i < size; i++)
//         os << arr[i] << " ";
//     return os;
// }
//重载标准输出流运算符 <<,将类的类型限定为const，保证该对象不能被修改
ostream &operator<<(ostream &os, const MyIArray &arr) {
    int size = arr.length();
    for (int i = 0; i < size; i++)
        os << arr[i] << " ";
    return os;
}

// int main() {
//     //调用有参构造，申请内存创建数组
//     MyIArray arr1(20);
//     int c = 10, i, size = arr1.length(); //调用函数length，返回数组的长度
//     for (i = 0; i < size; i++)
//         //调用重载运算符[]，返回的是相应数组偏移量的元素的引用，注意：数组返回的是左值
//         arr1[i] = c++;
//
//     // for (i = 0; i < size; i++)
//     //     cout << arr1[i] << " ";
//     // cout << endl;
//
//     //调用重载运算符 << ,直接使用标准输出打印MyIArray类
//     cout << arr1 << endl;
//
//     //调用拷贝构造，对arr1进行深拷贝，为arr2分配相同大小的内存，把所有arr1中数组元素拷贝到arr2的数组中
//     MyIArray arr2(arr1);
//
//     cout << arr2 << endl;
//
//     // for (i = 0; i < size; i++)
//     //     cout << arr2[i] << " ";
//     // cout << endl;
//
//     MyIArray arr3(1);
//     //调用类的重载操作符=，以arr2作为模板进行深拷贝后返回arr3的引用
//     arr3 = arr2;
//
//     cout << arr3 << endl;
//
//     // for (i = 0; i < size; i++)
//     //     cout << arr3[i] << " ";
//     // cout << endl;
//     // MyIArray *pp = &arr3;
//     cout << (arr3 == arr2) << endl;
//     cout << (arr3 != arr2) << endl;
//     return 0;
// }
