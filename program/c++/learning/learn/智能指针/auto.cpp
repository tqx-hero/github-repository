//
// Created by Administrator on 2026/7/23.
//
#include <iostream>
#include <list>
#include <unordered_map>

namespace tpr {
    class A {
    public:
        A(int num, const std::string &name)
            : num(num),
              name(name) {
        }

        int num;
        std::string name;
    };


    class Demo {
    public:
        struct Node {
            int key;
            int val;
            std::shared_ptr<Node> next;

            Node(int key, int val)
                : key(key),
                  val(val), next(nullptr) {
            }
        };

        std::shared_ptr<Node> head;
    };
}

// int main() {
//     using namespace std;
//     // std::unique_ptr<int> ip(new int);
//     // *ip = 10;
//     // cout << *ip << endl;
//     // std::unique_ptr<string> strp = make_unique<string>("1111111111111abcd");
//     // (*strp)[0] = 'd';
//     // strp->at(1) = 'f';
//     // cout << *strp << endl;
//     // using  ATpye = tpr::A;
//     // std::unique_ptr<ATpye> ap = make_unique<ATpye>(10,"aaa");
//     // ap->name[1]='c';
//     // cout << ap->name << endl;
//     // auto && pointer = ap.get();
//
//     // using namespace tpr;
//     // using demoType = Demo::Node;
//     // shared_ptr<demoType> head = make_shared<demoType>(0, 1);
//     // shared_ptr<demoType> n1 = make_shared<demoType>(1, 2);
//     // auto cur = head;
//     // cur->next = n1;
//     // cur = cur->next;
//     // cur->next = make_shared<demoType>(3, 4);
//     // while (head) {
//     //     cout << head->val << endl;
//     //     head = head->next;
//     // }
//
//     unordered_map<int, unique_ptr<string> > cache;
//     cache.try_emplace(1, make_unique<string>("abc"));
//     if (cache.count(1)) {
//         unordered_map<int, unique_ptr<string> >::iterator iter = cache.find(1);
//         cout << *iter->second << endl;
//         (*iter->second)[0] = '1';
//         cout << *iter->second << endl;
//     }
//     list<int> list;
//     return 0;
// }
