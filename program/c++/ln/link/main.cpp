//
// Created by Administrator on 2026/7/2.
//
#include "ListNode.h"
#include <iostream>

#include "LinkList.h"
using namespace std;

//struct 属性默认为public
struct B {
private:
    int num;
};

//函数属于类，变量属于对象，同一个类的函数可以访问这个类的对象所有成员变量
//class 属性缺省为private
//struct 属性缺省为public
class A {
    int num;

public:
    void set(int num) {
        this->num = num;
    }

    void get(A *a) {
        cout << a << " 的num = " << a->num << endl;
    }
};

// int main() {
//     A *a = new A();
//     A *aa = new A();
//     a->set(10);
//     aa->get(a);
//     delete aa;
//     delete a;
//     return 0;
// }


// int main() {
//     // LIST_PTR node5 = new ListNode(5, nullptr);
//     // LIST_PTR node4 = new ListNode(4, node5);
//     // LIST_PTR node3 = new ListNode(3, node4);
//     // LIST_PTR node2 = new ListNode(2, node3);
//     // LIST_PTR node1 = new ListNode(1, node2);
//     // LIST_PTR cur = node1;
//     // while (cur) {
//     //     cout << "value = " << cur->val << endl;
//     //     cur = cur->next;
//     // }
//     // delete node5;
//     // delete node4;
//     // delete node3;
//     // delete node2;
//     // delete node1;
//
//     LinkList *list = new LinkList();
//     list->addFirst(new ListNode(5));
//     list->addFirst(new ListNode(4));
//     list->addFirst(new ListNode(3));
//     list->addFirst(new ListNode(2));
//     list->addFirst(new ListNode(1));
//     LIST_PTR cur = list->getHead();
//     while (cur) {
//         cout << "value = " << cur->val << endl;
//         cur = cur->next;
//     }
//     delete list;
//     list = nullptr;
//     return 0;
// }
