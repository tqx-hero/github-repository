package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 克鲁斯卡尔算法实现最小生成树（邻接矩阵）
 * @date 2026/3/30 17:33
 */
public class KruskalMSTree {
    private KEdgeEntry[] buckets;
    //这个代表顶点的数量
    private int size;
    private int edgNum;
    private static final double INIT_MIN_WEIGHT = Double.MAX_VALUE - 1;
    //    private static final String KEY_PREFIX = ":";
    private List<KEdgeEntry> edges;
    //认祖归宗
    private int[] parent;

    @Override
    public String toString() {
        return "KruskalMSTree{" +
                "buckets=" + Arrays.toString(buckets) +
                ", size=" + size +
                ", edgNum=" + edgNum +
                ", edges=" + edges +
                '}';
    }

    private static class KEdgeEntry {
        Object iVal, jVal;
        int iIdx, jIdx;
        double weight;

        @Override
        public String toString() {
            return "KEdgeEntry{" +
                    "iIdx=" + iIdx +
                    ", iVal=" + iVal +
                    ", jVal=" + jVal +
                    ", jIdx=" + jIdx +
                    ", weight=" + weight +
                    '}';
        }

        public KEdgeEntry(int iIdx, Object iVal, int jIdx, Object jVal, double weight) {
            this.iIdx = iIdx;
            this.iVal = iVal;
            this.jIdx = jIdx;
            this.jVal = jVal;
            this.weight = weight;
        }
    }

    private boolean illegal(double w) {
        return w > 0 && w < INIT_MIN_WEIGHT;
    }

    //加载边集合
    //返回类型： {key=1:2 value=20.0}
    private void initEdges(double[][] edges, Object[] vertex) {
        int maxLen = vertex.length;
        //搜寻上三角，将边的信息放入map
        for (int i = 0; i < maxLen; i++) {
            for (int j = i + 1; j < maxLen; j++) {
                double weight = edges[i][j];
                if (illegal(weight)) {
                    this.edges.add(new KEdgeEntry(i, vertex[i], j, vertex[j], weight));
                }
            }
        }
    }

    //初始化并集，让自己成为自己的祖宗
    private void initUnion(int size) {
        this.parent = new int[size];
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    public void initTree(int size) {
        this.size = size;
        //边数量为顶点数-1
        this.buckets = new KEdgeEntry[size - 1];
        this.edgNum = 0;
        this.edges = new ArrayList<>();
        initUnion(size);
    }


    //往上倒，找到自己的祖宗

    /**
     * 核心算法，找到自己的根节点
     *
     * @param x
     * @return
     */
    private int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    private void union(int x, int y) {
        int fx = find(x);
        int fy = find(y);
        if (fx != fy)
            parent[fy] = fx;
    }

    public KruskalMSTree createTree(ArrayMetrex.Graph graph) {
        if (graph == null)
            return this;
        int size = graph.vs;
        Object[] vertex = graph.vertexs;
        double[][] edges = graph.edges;
        initTree(size);
        initEdges(edges, vertex);
        //按照权重正序排序
        this.edges.sort(Comparator.comparingDouble(o -> o.weight));
        for (KEdgeEntry entry : this.edges) {
            int u = entry.iIdx;
            int v = entry.jIdx;
            //需要查看该条边与已经存在的边是否构成环
            if (find(u) == find(v))
                continue;
            //找到相关的边信息了
            //1、添加边到桶
            buckets[edgNum++] = entry;
            //将顶点信息合并，维护parent[]
            union(u, v);
            if (edgNum == size - 1)
                break;
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
        KruskalMSTree kruskalMSTree = new KruskalMSTree();
        KruskalMSTree tree = kruskalMSTree.createTree(graph);
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
