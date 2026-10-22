//
// Created by 田庆新 on 2026/9/9.
//
/**
* 207. 课程表
中等
相关标签
premium lock icon
相关企业
提示
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。



示例 1：

输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
示例 2：

输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成​课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。


提示：

1 <= numCourses <= 2000
0 <= prerequisites.length <= 5000
prerequisites[i].length == 2
0 <= ai, bi < numCourses
prerequisites[i] 中的所有课程对 互不相同
 * @return
 */
#include <queue>
#include <iostream>
#include <vector>
using namespace std;
//有向图的无环检测问题
//需要使用拓扑排序
//条件给出的是
class Solution {
    //边的结构体
    struct EdgeNode {
        //入渡边下标、出渡边下标
        int in_index, out_index;
        //入渡边与出渡边的next
        EdgeNode *in_next, *out_next;

        EdgeNode(int in_index, int out_index, EdgeNode *in_next = nullptr,
                 EdgeNode *out_next = nullptr)
            : in_index(in_index),
              out_index(out_index),
              in_next(in_next),
              out_next(out_next) {
        }
    };

    //十字链表节点的
    struct CrossLinkedNode {
        //当前下标、入渡边个数、出渡边个数
        int index, in_size, out_size;
        //入渡边与出渡边的链表头结点
        EdgeNode *out_edge, *in_edge;

        CrossLinkedNode(int index, int in_size = 0, int out_size = 0,
                        EdgeNode *out_edge = nullptr, EdgeNode *in_edge = nullptr)
            : index(index),
              in_size(in_size),
              out_size(out_size),
              out_edge(out_edge),
              in_edge(in_edge) {
        }

    };

    //顶点个数
    int vertex_size;
    //十字链表桶
    vector<CrossLinkedNode *> arr;

    void init_arr() {
        arr.resize(vertex_size);
        for (int i = 0; i < vertex_size; ++i) {
            //为每个顶点分配内存，生成节点，包括哨兵节点
            arr[i] = new CrossLinkedNode(i, 0, 0,
                                         new EdgeNode(-1, -1),
                                         new EdgeNode(-1, -1));
        }
    }

    //构建十字链表
    void build_crossLinkList(int numCourses, vector<vector<int> > &prerequisites) {
        vertex_size = numCourses;
        init_arr();
        for (auto &pa: prerequisites) {
            //获取当前边的入渡与出渡顶点
            int out_index = pa[0], in_index = pa[1];
            //新建这条边节点
            EdgeNode *newNode = new EdgeNode(in_index, out_index);
            auto out_node = arr[out_index], in_node = arr[in_index];
            //连接到出入顶点的相关边链表中
            newNode->out_next = out_node->out_edge->out_next;
            out_node->out_edge->out_next = newNode;
            out_node->out_size++;
            newNode->in_next = in_node->in_edge->in_next;
            in_node->in_edge->in_next = newNode;
            in_node->in_size++;
        }
    }

    //拓扑排序，返回遍历到的顶点数
    int topology_order() {
        int count = 0;
        queue<CrossLinkedNode *> cross_cache;
        for (auto cross: arr) {
            //统计入渡边为0的节点放入队列
            if (cross->in_size == 0) {
                cross_cache.push(cross);
            }
        }
        //以所有入渡为0的顶点出发，进行拓扑排序，并统计计数count
        while (!cross_cache.empty()) {
            auto linked_node = cross_cache.front();
            cross_cache.pop();
            count++;
            //遍历该节点的出渡边集合，更新入渡顶点的入渡数量
            EdgeNode *out_edge_ptr = linked_node->out_edge->out_next;
            while (out_edge_ptr) {
                //获取入渡顶点
                int in_idx = out_edge_ptr->in_index;
                //要去掉这条边，所以需要减去它的入渡
                arr[linked_node->index]->out_size--;
                //减完入渡边数量之后，查看该顶点的入渡边是否归0，归0则放入队列
                if (--arr[in_idx]->in_size == 0) {
                    cross_cache.push(arr[in_idx]);
                }
                out_edge_ptr = out_edge_ptr->out_next;
            }
        }
        return count;
    }

public:
    bool canFinish(int numCourses, vector<vector<int> > &prerequisites) {
        int size = static_cast<int>(prerequisites.size());
        //如果没有边，表明课程之间没有依赖关系，肯定能完成.
        if (!size || numCourses == 1)
            return true;
        //需要构造一个十字链表，从入渡边的顶点出发进行拓扑排序，最后遍历到的顶点个数等于numCourses，返回true
        //小于numCourses返回false
        //构建十字链表
        build_crossLinkList(numCourses, prerequisites);
        //拓扑排序
        return topology_order() == numCourses;
    }
};

// int main() {
//     //numCourses = 2, prerequisites = [[1,0],[0,1]]
//     // vector<vector<int> > prerequisites{
//     //     {1, 0},
//     //     {0, 1}
//     // };
//     //numCourses = 2, prerequisites = [[1,0]]
//     vector<vector<int> > prerequisites{
//         {1, 0}
//     };
//     int numCourses = 2;
//     Solution sl;
//     cout << sl.canFinish(numCourses, prerequisites) << endl;
//     return 0;
// }
