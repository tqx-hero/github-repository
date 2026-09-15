package com.tqx.top;

import java.lang.module.FindException;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 拓扑排序
 * 从入度为0的顶点开始，
 * 每次去除这个顶点后再找入度为0的顶点，直到所有顶点都被找到
 * 拓扑排序结果不唯一
 * 可以将这些入度为0的点都放到一个数据结构里：栈或者队列
 * 由于这两个数据结构的差异，弹出的顶点顺序不同，依次删除入度信息的顺序也不同
 * 导致结果也不相同，但都是合理的拓扑排序
 * @date 2026/4/16 17:43
 */
public class TopSort {

    private TNode[] graph;
    private int count;

//    private static class InNode {
//        int index;
//        InNode next;
//        double cost;
//
//        public InNode(int index, InNode next, double cost) {
//            this.index = index;
//            this.next = next;
//            this.cost = cost;
//        }
//    }

    private static class OutNode {
        int index;
        OutNode next;
        double cost;

        @Override
        public String toString() {
            return "OutNode{" +
                    "cost=" + cost +
                    ", index=" + index +
                    ", next=" + next +
                    '}';
        }

        public OutNode(int index, OutNode next, double cost) {
            this.index = index;
            this.next = next;
            this.cost = cost;
        }
    }

    private static class TNode {
        //入度边数
        int indegree;
        OutNode out;
        String vertex;

        public TNode(String vertex) {
            this.vertex = vertex;
            indegree = 0;
        }

        @Override
        public String toString() {
            return "TNode{" +
                    " indegree=" + indegree +
                    ", out=" + out +
                    ", vertex='" + vertex + '\'' +
                    '}';
        }
    }

    @Override
    public String toString() {
        return "TopSort{" +
                "count=" + count +
                ", graph=" + Arrays.toString(graph) +
                '}';
    }

    public TopSort(String[] arr) {
        if (arr == null || arr.length == 0)
            throw new NullPointerException("加载数组不能为空");
        this.count = arr.length;
        this.graph = new TNode[count];
        for (int i = 0; i < count; i++)
            graph[i] = new TNode(arr[i]);
    }

    // 1->2 10.00  {{1,2,10.00}}
    public void init(Object[][] arcs) {
        if (arcs == null || arcs.length == 0)
            return;
        for (Object[] a : arcs) {
            int out = (int) a[0];
            int in = (int) a[1];
            double cost = (double) a[2];
            graph[out].out = new OutNode(in, graph[out].out, cost);
            graph[in].indegree++;
        }
    }

    private void addQueue(int i, ArrayDeque<Integer> queue, boolean[] visited, int[] indegree) {
        if (indegree[i] == 0) {
            queue.offer(i);
            visited[i] = true;
        }
    }

    // ===================== 核心：非递归枚举所有拓扑排序 =====================
    // 思路：
    // 1. 用栈保存每一步状态（候选列表、当前入度、当前路径、指针、访问标记）
    // 2. 每次选一个入度为0的点，压入【回退状态】和【前进状态】
    // 3. 遍历出边削减后继入度，生成新候选
    // 4. 路径长度 == 节点数时，收集一条完整拓扑序
    // 5. 全程非递归，无栈溢出，状态完全隔离

    //获取全部拓扑排序
    //通过压栈形式。
    //将要处理的数据封装，逐次压入栈内，运用栈的递归回溯特性完成多种排列组合
    //而且没有递归OOM的风险
    public List<List<String>> sortAll() {
        ArrayList<List<String>> resList = new ArrayList<>();
        ArrayDeque<State> stack = new ArrayDeque<>();
        // 全局本轮结果（持续累积，直到收集满一轮）
        ArrayList<Integer> resultList = new ArrayList<>();
        //加载入度信息
        int[] indegree = new int[count];
        boolean[] visited = new boolean[count];
        //候选人名单
        List<Integer> candidates = new ArrayList<>();
        for (int i = 0; i < count; i++) {
            indegree[i] = graph[i].indegree;
            //入度为0的直接加入候选人名单
            if (indegree[i] == 0) {
                visited[i] = true;
                candidates.add(i);
            }
        }
        // 初始状态入栈
        State state = new State(candidates, indegree, new ArrayList<>(), 0, visited);
        stack.push(state);
        while (!stack.isEmpty()) {
            State stateInfo = stack.pop();
            List<Integer> backCandidate = stateInfo.candidates;
            List<Integer> backList = stateInfo.result;
            int[] in = stateInfo.indegree;
            boolean[] backVisited = stateInfo.visited;
            int ptr = stateInfo.ptr;
            // 本轮结果为空时，从状态中恢复现场
            if (resultList.isEmpty()) {
                visited = Arrays.copyOf(backVisited, count);
                indegree = Arrays.copyOf(in, count);
                resultList = new ArrayList<>(backList);
            }
            if (!backCandidate.isEmpty()) {
                // 取当前指针指向的候选节点
                Integer i = backCandidate.get(ptr);
                // 该节点未在当前路径中，加入路径
                if (!resultList.contains(i)) {
                    resultList.add(i);
                    // 已收集所有节点 → 形成一条完整拓扑序
                    if (resultList.size() >= count) {
                        ArrayList<String> s = new ArrayList<>();
                        for (Integer x : resultList)
                            s.add(graph[x].vertex);
                        resList.add(s);
                        // 清空全局状态，准备下一轮排列
                        resultList.clear();
                        Arrays.fill(indegree, 0);
                        Arrays.fill(visited, false);
                        continue;
                    }
                    // ===================== 压栈：回退状态 =====================
                    // 指针+1，表示“下一次从下一个候选开始”
                    if (backCandidate.size() > ptr + 1)
                        stack.push(new State(backCandidate, in, backList, ptr + 1, backVisited));
                    // ===================== 压栈：前进候选 =====================
                    // 移除当前节点，剩下候选继续排列
                    ArrayList<Integer> forwardCandidate = new ArrayList<>(backCandidate);
                    forwardCandidate.remove(i);
                    if (!forwardCandidate.isEmpty())
                        stack.push(new State(forwardCandidate, in, resultList, 0, backVisited));
                }
                // ===================== 处理出边：削减后继入度 =====================
                OutNode node = graph[i].out;
                ArrayList<Integer> canDi = new ArrayList<>();
                while (node != null) {
                    int idx = node.index;
                    indegree[idx]--;
                    // 入度减为0 → 加入新候选
                    if (indegree[idx] == 0 && !visited[idx]) {
                        canDi.add(idx);
                        visited[idx] = true;
                    }
                    node = node.next;
                }
                // 有新候选 → 压入新状态继续扩展
                if (!canDi.isEmpty())
                    stack.push(new State(canDi, Arrays.copyOf(indegree, count),
                            new ArrayList<>(resultList), 0, Arrays.copyOf(visited, count)));
            }
        }
        return resList;
    }
    // 栈中保存的状态快照：每一步的现场
    private static class State {
        boolean[] visited;    // 访问标记
        List<Integer> result; // 当前已选路径
        List<Integer> candidates; // 当前入度0候选
        int[] indegree;       // 当前入度数组
        int ptr;              // 遍历候选的指针（用于排列）

        public State(List<Integer> candidates, int[] indegree, List<Integer> result, int ptr, boolean[] visited) {
            this.candidates = candidates;
            this.indegree = indegree;
            this.result = result;
            this.ptr = ptr;
            this.visited = visited;
        }
    }


    public String[] sort() {
        String[] result = new String[count];
        boolean[] visited = new boolean[count];
        int[] indegree = new int[count];
        ArrayDeque<Integer> queue = new ArrayDeque<>();
        //将所有入度为0的顶点下标放入队列
        for (int i = 0; i < count; i++) {
            indegree[i] = graph[i].indegree;
            addQueue(i, queue, visited, indegree);
        }
        int index = 0;
        while (!queue.isEmpty()) {
            Integer idx = queue.poll();
            //添加顶点
            result[index++] = graph[idx].vertex;
            //遍历所有排除该顶点的顶点
            OutNode out = graph[idx].out;
            while (out != null) {
                indegree[out.index]--;
                //入度为0的添加到队列
                addQueue(out.index, queue, visited, indegree);
                out = out.next;
            }
        }
        if (index != count)
            throw new FindException("该结构有环!");
        return result;
    }

    // ===================== 测试 =====================
    public static void main(String[] args) {
        Object[][] obj = new Object[][]{
                {0, 1, 1.00},
                {0, 3, 1.00},
                {0, 2, 1.00},
                {1, 3, 1.00},
                {1, 4, 1.00},
                {2, 5, 1.00},
                {3, 2, 1.00},
                {3, 5, 1.00},
                {3, 6, 1.00},
                {4, 3, 1.00},
                {4, 6, 1.00},
                {6, 5, 1.00}
        };
        TopSort graph = new TopSort(new String[]{"v1", "v2", "v3", "v4", "v5", "v6", "v7"});
//        TopSort graph = new TopSort(new String[]{"v1", "v2", "v3"});
        graph.init(obj);
//        System.out.println(graph);
//        System.out.println(Arrays.toString(graph.sort()));
        List<List<String>> allTopSort = graph.sortAll();
        System.out.println("所有拓扑排序数量：" + allTopSort.size());
        for (List<String> list : allTopSort) {
            System.out.println(list);
        }
    }

}
