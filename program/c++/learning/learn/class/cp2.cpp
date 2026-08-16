//
// Created by Administrator on 2026/7/10.
//
#include <iostream>
using namespace std;

class Test {
    int num;
    int sex;

public:
    Test() : num(0), sex(0) {
    }

    Test(int num, int sex)
        : num(num),
          sex(sex) {
        cout << "有参构造被调用" << endl;
    }

    Test(const Test &ann) : num(ann.num), sex(ann.sex) {
        cout << "拷贝构造被调用" << endl;
    }

    Test &operator=(const Test &ann) {
        this->num = ann.num;
        this->sex = ann.sex;
        cout << "重载运算符函数被调用" << endl;
        return *this;
    }

    ~Test() {
        cout << "~Test" << endl;
    }
};

//这样以对象作为返回值，会额外调用一次拷贝构造，生成一个匿名对象返回
//所以日常还是以指针或者引用的形式返回，
//必须在堆上开辟空间，不能直接用栈上的局部变量了(栈在函数执行结束后会销毁，指针成了野指针，一定要避免)
//返回时返回这个对象的指针或者引用
Test func() {
    cout << "func begin" << endl;
    Test ts(10, 20);
    cout << "func end" << endl;
    //这边会调用拷贝构造，生成一个匿名对象Test,然后把这个匿名对象返回
    //并且会调用ts的析构函数，销毁局部变量ts
    return ts;
}

//改进上述函数，直接在堆上开辟空间，返回它的引用
Test &func_ref() {
    Test *ts = new Test(10, 20);
    return *ts;
}

//或者直接返回指针，同样需要注意，一定要是在堆上申请空间返回，绝对不能在栈上直接申请空间，否则会成为野指针
Test *func_ptr() {
    return new Test(10, 20);
}


void fu_test() {
    cout << "fu_test begin" << endl;
    //这里返回的对象不再是func函数内生成的局部变量ts，而是一个匿名对象，调用了匿名对象的拷贝构造生成的
    //返回到这里后只能通过用同类对象去接收它，给它命名，这样就能够在这个函数内使用它
    //如果没有给它命名，会直接调用析构函数，销毁它
    // func();
    //如果以下面这种方式，或者用Test t=func();的形式，就是给这个匿名对象起了一个名字
    //这样函数内就能正常使用该对象，它不再是匿名对象，编译器不会立即调用它的析构函数
    //而是等函数执行结束，return之前调用
    // Test t(func());

    //如果是这种形式，首先会调用ts的无参构造，生成局部变量ts
    //再去调用func函数，生成匿名对象返回
    //最后是赋值操作，即利用操作符=进行赋值，如果重载了运算符，调用重载后的函数，没有重载，则调用默认的
    Test ts;
    //匿名对象没有给它起名，相当于没有接收它，仅仅作为了一个参数，调用了ts的重载运算符函数，
    //所以在重载操作符函数执行后，由于没有接收匿名对象，这个函数内就无法使用它，所以编译器会直接对其进行析构，销毁
    ts = func();

    cout << "fu_test end" << endl;
}

// int main() {
//     fu_test();
//     return 0;
// }
