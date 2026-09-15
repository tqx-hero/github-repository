package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 迪杰斯特拉算法查找最短路径
 * @date 2026/3/31 11:04
 */
public class ShortestPath {

    private static final double INF = 1e18;
    private SPEntry[] resultBucket;
    //顶点总数量
    private int size;

    @Override
    public String toString() {
        return "ShortestPath{" +
                "resultBucket=" + Arrays.toString(resultBucket) +
                ", size=" + size +
                '}';
    }

    private static class SPEntry {
        int index;
        Object value;
        //每次重点更新
        double weight;   //存储从初始点到该顶点的最短距离/权重
        //判断是否已经在S集合中遍历查找T集合
        //该状态仅在遍历查找T集合时设置
//        boolean visited;

        @Override
        public String toString() {
            return "SPEntry{" +
                    "index=" + index +
                    ", value=" + value +
                    ", weight=" + weight +
                    '}';
        }

        public SPEntry(int index, Object value, double weight) {
            this.index = index;
            this.value = value;
            this.weight = weight;
        }
    }

    //初始化对象属性，添加起始顶点v0
    private void init(int size, int v0, Object[] vertex) {
        this.size = size;
        resultBucket = new SPEntry[size];
        for (int i = 0; i < size; i++)
            resultBucket[i] = new SPEntry(i, vertex[i], INF);
        //设置起始点
        resultBucket[v0].weight = 0;
    }

    private static boolean illegal(double weight) {
        return weight >= 0 && weight < INF;
    }


    /**
     * 用小顶堆方式实现最短路径
     *
     * @param graph
     * @param start
     * @return
     */
    public ShortestPath shortestPathByHeap(ArrayMetrex.Graph graph, int start) {
        int size;
        if (graph == null || start < 0 || start >= (size = graph.vs))
            throw new IllegalArgumentException("输入的图参数有误");
        double[][] edges = graph.edges;
        Object[] vertex = graph.vertexs;
        this.size = size;
        this.resultBucket = new SPEntry[size];
        //创建小顶堆，制定规则：按照权重排序
        PriorityQueue<SPEntry> minHeap = new PriorityQueue<>(Comparator.comparingDouble(e -> e.weight));
        //初始化堆
        for (int i = 0; i < size; i++)
            resultBucket[i] = new SPEntry(i, vertex[i], INF);
        resultBucket[start].weight = 0;
        boolean[] visited = new boolean[size];
        minHeap.add(new SPEntry(start, vertex[start], 0));
        while (!minHeap.isEmpty()) {
            SPEntry minNode = minHeap.poll();
            int currentIdx = minNode.index;
            if (visited[currentIdx])
                continue;
            double currentWeight = minNode.weight;
            resultBucket[currentIdx].weight = currentWeight;
            visited[currentIdx] = true;
            for (int i = 0; i < size; i++) {
                double w = edges[currentIdx][i];
                if (visited[i] || !illegal(w))
                    continue;
                double nowWeight = w + currentWeight;
                //判断是否小于当前与初始点的权重，小于则更新
                if (nowWeight < resultBucket[i].weight) {
                    resultBucket[i].weight = nowWeight;
                    minHeap.add(new SPEntry(i, vertex[i], nowWeight));
                }
            }
        }
        return this;
    }

    public ShortestPath calculate(ArrayMetrex.Graph graph, int v0) {
        if (graph == null || v0 < 0 || v0 >= graph.vs)
            throw new ArrayIndexOutOfBoundsException("输入的下标越界!");
        Object[] vertex = graph.vertexs;
        double[][] edges = graph.edges;
        int vSize = graph.vs;
        init(vSize, v0, vertex);
        //是否已添加到U集合
        boolean[] visited = new boolean[size];
        for (int c = 0; c < size; c++) {

            int u = -1;
            double minW = INF;
            //找已添加到集合中的最新顶点
            for (int i = 0; i < size; i++) {
                double w = resultBucket[i].weight;
                if (!visited[i] && illegal(w) && w < minW) {
                    u = i;
                    minW = w;
                }
            }

            if (u < 0)
                break;
            //更新与起始点的权重
            for (int k = 0; k < size; k++) {
                double kk = edges[u][k], mn;
                if (!visited[k] && illegal(kk)
                        && (mn = kk + minW) < resultBucket[k].weight) {
                    resultBucket[k].weight = mn;
                }
            }

            visited[u] = true;

        }
        return this;
    }

    public static void main(String[] args) {
        String[] num = {"a", "b", "c", "d", "e", "f"};
        HashMap<String, Integer> map = new HashMap<>();
        map.put("a:b", 10);
        map.put("a:d", 10);
        map.put("a:c", 5);
//        map.put("c:d", 2);
        map.put("c:f", 2);
//        map.put("e:d", 2);
        map.put("e:b", 2);

        ArrayMetrex metrex = new ArrayMetrex();
        //创建无向网
        ArrayMetrex.Graph graph = metrex.createGraph(num, map);
        ShortestPath path = new ShortestPath();
//        ShortestPath calculate = path.calculate(graph, 0);
        ShortestPath calculate = path.shortestPathByHeap(graph, 0);
        System.out.println(calculate);
//        PrimMSTree primMsTree = new PrimMSTree();
//        PrimMSTree tree = primMsTree.buildTree(graph);
//        System.out.println(tree);
        //深度优先
//        metrex.dfs(graph, 0);
        //广度优先
//        metrex.bfs(graph, 0);
        //创建有向网
//        Graph graph = metrex.createDirectionGraph(num, map);
//        System.out.println(graph);
//        graph.getEdges();
//        graph.
    }
}
