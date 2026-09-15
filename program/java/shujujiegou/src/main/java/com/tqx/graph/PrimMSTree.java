package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 构建邻接矩阵的最小生成树 Prim算法
 * 最终形式：
 * Entry[] arr:
 * Entry{
 * Object value;
 * int parentIdx;
 * double weight;
 * }
 * 示例：
 * | index | value | parentIdx | weight |
 * | :---: | :---: | :-------: | :----: |
 * |   0   |   a   |    -1     |   1    |
 * |   1   |   b   |     0     |   5    |
 * |   2   |   c   |     0     |   3    |
 * |   3   |   d   |     2     |   4    |
 * @date 2026/3/30 13:58
 */
public class PrimMSTree {
    private static final double INIT_MIN_WEIGHT = Double.MAX_VALUE - 1;
    private MSTEntry[] buckets;
    private int size;
    private int eleNum;

    @Override
    public String toString() {
        return "MSTree{" +
                "buckets=" + Arrays.toString(buckets) +
                ", size=" + size +
                ", eleNum=" + eleNum +
                '}';
    }

    private static class MSTEntry {
        Object value;
        int parentIdx;
        double weight;
        //所在原图顶点的下标
//        int graphIdx;

        public MSTEntry(Object value) {
            this.value = value;
        }

        @Override
        public String toString() {
            return "MSTEntry{" +
                    " value=" + value +
                    ", parentIdx=" + parentIdx +
                    ", weight=" + weight +
                    '}';
        }

        public MSTEntry(int parentIdx, Object value, double weight) {
            this.parentIdx = parentIdx;
            this.value = value;
            this.weight = weight;
        }
    }

    public PrimMSTree() {
    }

//    public MSTree(int size) {
//        this.size = size;
//        buckets = new MSTEntry[size];
//    }

    private void initTree(int size) {
        this.size = size;
        this.buckets = new MSTEntry[size];
        this.eleNum = 0;
    }

//    private Map<Integer, Set<Integer> >

    //加载桶，找出最小权重的两个顶点
    //放入桶位
    //返回已被添加的标记数组，记录vertex中顶点是否已被添加到树上
    // 0：未被添加；1:已被添加
    private void initBucket(double[][] edges, Object[] vertex) {
        double minWeight = INIT_MIN_WEIGHT;
        int u = 0, v = 0;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j++) {
                double weight = edges[i][j];
                //判断是否是权重
                if (ArrayMetrex.Graph.illegal(weight) && weight < minWeight) {
                    minWeight = weight;
                    u = i;
                    v = j;
                }
            }
        }
        //添加权重最小的两个节点
        buckets[u] = new MSTEntry(-1, vertex[u], -1);
        buckets[v] = new MSTEntry(u, vertex[v], minWeight);
        eleNum = 2;
        //将这两个权重最小的节点下标标注为已被添加
    }

//    private int bucketIdx(int i) {
//        return i % size;
//    }

    private boolean contains(int idx) {
        return buckets[idx] != null;
    }

    //Graph graph = metrex.createGraph(num, map);
    public PrimMSTree buildTree(ArrayMetrex.Graph graph) {
        if (graph == null)
            return null;
        double[][] edges = graph.edges;
        Object[] vertex = graph.vertexs;
        int size = graph.vs;
        initTree(size);
        initBucket(edges, vertex);
        while (eleNum < size) {
            double minWeight = INIT_MIN_WEIGHT;
            int minIdx = -1;
            int parentId = -1;
            //Prim算法查找权重最小的顶点
            for (int k = 0; k < size; k++) {
                if (!contains(k))
                    continue;
                for (int j = 0; j < size; j++) {
                    double weight = edges[k][j];
                    //判断是否是权重
                    //合法的权重、权重比之前记录的小、元素还没有添加到桶位
                    if (ArrayMetrex.Graph.illegal(weight) && weight < minWeight && !contains(j)) {
                        minIdx = j;
                        parentId = k;
                        minWeight = weight;
                    }
                }
            }
            //查找出来，放入桶中
            if (parentId >= 0) {
                buckets[minIdx] = new MSTEntry(parentId, vertex[minIdx], minWeight);
                eleNum++;
            }
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
        PrimMSTree primMsTree = new PrimMSTree();
        PrimMSTree tree = primMsTree.buildTree(graph);
        System.out.println(tree);
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
