//
// Created by Administrator on 2026/7/19.
//
#include <iostream>
#include <map>

// int main() {
//     std::map<int,int> treeMap;
//     //以下两种数对创建方式等价，都是调用pair的有参构造，生成的变量在栈上
//     treeMap.insert(std::pair(10,20));
//     treeMap.insert(std::make_pair(11,20));  //以上两种方式，即insert，会先对临时对象进行拷贝构造，在堆上生成新的节点，再插入，性能差
//     //emplace，直接传入键值对，容器内部会原地构造，在堆上开辟空间，没有额外的一次拷贝构造。但是节点创建时机太早。
//     //一上来就创建，不管是否存在，如果存在再销毁新创建的对象，这种情况下多了一次创建销毁的开销
//     const auto & pair = treeMap.emplace(10,10);
//     std::cout << pair.second << _STD endl;
//     treeMap.emplace(100,10);
//
//     //try_emplace与emplace同样也是原地构造对象，优化了对象的创建时机，只有发现对象不存在容器内时才会创建对象，c++17出现的新特性，建议使用
//     treeMap.try_emplace(80,1000);
//     //无论以上哪种方式，都只是针对插入操作，如果对象存在，则不会修改对象的值。
//     treeMap.try_emplace(100,1000);
//     //对数据进行插入，如果已经存在key，则修改值
//     //返回值的第二个参数bool，仅仅是判断插入是否成功，即false是key已经存在，插入失败，即使该函数修改成功
//     const auto & p = treeMap.insert_or_assign(100,10);
//     std::cout << p.second << _STD endl;
//
//     //直接查找，返回key关联对象的引用，如果不存在则插入，存在返回可以直接修改
//     //但是如果只是想查询，这种方式也会插入一条新数据，会污染容器。
//     //仅仅适用于key已经确定存在或者就是要插入或修改数据的场景。
//     //如果不确定key是否存在，不要使用。
//     // treeMap[10]=3000;
//     //下面这条语句仅仅查询了以下key=300的引用，就直接插入了一条数据
//     auto & ex = treeMap[300];
//     for (auto& n : treeMap) {
//         _STD cout << n.first << " : " << n.second <<_STD endl;;
//     }
//     return 0;
// }
