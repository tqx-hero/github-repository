package com.tqx.graph;


import java.util.Arrays;
import java.util.Comparator;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 迪杰斯特拉算法求最短路径
 * 运用小顶堆，按照权重升序排列，这样每次都能拿取最小权重的顶点
 * @date 2026/4/17 9:50
 */
public class DijkstraAlgorithm {

    private DNode[] graph;
    private int count;

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
            this.cost = cost;
            this.index = index;
            this.next = next;
        }
    }

    @Override
    public String toString() {
        return "DijkstraAlgorithm{" +
                "count=" + count +
                ", graph=" + Arrays.toString(graph) +
                '}';
    }

    private static class DNode {
        String vertex;
        OutNode out;

        public DNode(String vertex) {
            this.vertex = vertex;
        }

        @Override
        public String toString() {
            return "DNode{" +
                    "out=" + out +
                    ", vertex='" + vertex + '\'' +
                    '}';
        }
    }

    //定义比较器对象
    //用于放入堆中进行比较
    private static class ComparableNode implements Comparable<ComparableNode> {
        int index;
        double cost;

        public ComparableNode(double cost, int index) {
            this.cost = cost;
            this.index = index;
        }

        @Override
        public int compareTo(ComparableNode o) {
            return Double.compare(this.cost, o.cost);
        }
    }

    public DijkstraAlgorithm(String[] arr) {
        if (arr == null || arr.length == 0)
            throw new NullPointerException("加载数组不能为空");
        this.count = arr.length;
        this.graph = new DNode[count];
        for (int i = 0; i < count; i++)
            graph[i] = new DNode(arr[i]);
    }

    public void build(Object[][] arcs) {
        if (arcs == null)
            return;
        for (Object[] a : arcs) {
            int out = (int) a[0];
            int in = (int) a[1];
            double cost = (double) a[2];
            graph[out].out = new OutNode(in, graph[out].out, cost);
        }
    }

    private static class Path {
        int index;
        String vertex;
        double cost;
        Path parent;

        public Path(double cost, int index, String vertex) {
            this.cost = cost;
            this.index = index;
            this.vertex = vertex;
        }

        @Override
        public String toString() {
            return "Path{" +
                    "cost=" + cost +
                    ", index=" + index +
                    ", vertex='" + vertex + '\'' +
                    ", parent=" + parent +
                    '}';
        }

        public Path parent(Path parent) {
            this.parent = parent;
            return this;
        }

        public Path(double cost, int index, Path parent, String vertex) {
            this.cost = cost;
            this.index = index;
            this.parent = parent;
            this.vertex = vertex;
        }
    }

    public Path[] shortPath(int x) {
        Object[] obj = shortPathCalculate(x);
        int[] parent = (int[]) obj[0];
        double[] costs = (double[]) obj[1];
        Path[] p = new Path[count];
        for (int i = 0; i < count; i++) {
            int j = i;
            Path child = p[j] = new Path(costs[j], j, graph[j].vertex);
            while (parent[j] != -1) {
                int pi = parent[j];
                child.parent = new Path(costs[pi], pi, graph[pi].vertex);
                child = child.parent;
                j = pi;
            }
        }
        return p;
    }

    public String[] shortPathToStr(int x) {
        Object[] obj = shortPathCalculate(x);
        int[] parent = (int[]) obj[0];
        double[] costs = (double[]) obj[1];
        String[] strArr = new String[count];
        for (int i = 0; i < count; i++) {
            int j = i;
            StringBuilder sb = new StringBuilder();
            sb.append(graph[j].vertex);
            while (parent[j] != -1) {
                int pi = parent[j];
                sb.append(" >- ")
                        .append(graph[pi].vertex);
                j = pi;
            }
            strArr[i] = sb.reverse().append(" (").append(costs[i]).append(")").toString();
        }
        return strArr;
    }

    //从顶点下标x开始计算到所有顶点的最短路径
    private Object[] shortPathCalculate(int x) {
        if (x < 0 || x >= count)
            throw new ArrayIndexOutOfBoundsException("下标越界");
        //与顶点的最长路径
        boolean[] visited = new boolean[count];
        //定义顶点的parent
        int[] parent = new int[count];
        double[] costs = new double[count];
        Arrays.fill(costs, Double.MAX_VALUE - 1);
        costs[x] = 0;
        Arrays.fill(parent, -1);
        //顶点是否已经被添加
        PriorityQueue<ComparableNode> minHeap = new PriorityQueue<>();
        for (int i = 0; i < count; i++)
            minHeap.offer(new ComparableNode(costs[i], i));
        int con = 0;
        while (!minHeap.isEmpty()) {
            int idx = minHeap.poll().index;
            if (visited[idx])
                continue;
            visited[idx] = true;
            con++;
            if (con >= count)
                break;
            OutNode out = graph[idx].out;
            double baseCost = costs[idx];
            while (out != null) {
                //如果基础权重+自身到该顶点的权重< 记录的权重，
                //修改记录权重，并记录这个权重大小，与index
                int oi = out.index;
                if (!visited[oi]) {
                    double v = baseCost + out.cost;
                    if (v < costs[oi]) {
                        //修改记录权重/设置父节点为idx
                        costs[oi] = v;
                        parent[oi] = idx;
                        minHeap.offer(new ComparableNode(costs[oi], oi));
                    }
                }
                out = out.next;
            }
        }
        return new Object[]{
                parent,
                costs
        };
    }

    public static void main(String[] args) {
        Object[][] obj = new Object[][]{
                {0, 1, 2.00},
                {0, 3, 1.00},
                {1, 3, 3.00},
                {1, 4, 10.00},
                {2, 0, 4.00},
                {2, 5, 5.00},
                {3, 2, 2.00},
                {3, 4, 2.00},
                {3, 5, 8.00},
                {3, 6, 4.00},
                {4, 6, 6.00},
                {6, 5, 1.00}
        };
        DijkstraAlgorithm graph = new DijkstraAlgorithm(new String[]{"v1", "v2", "v3", "v4", "v5", "v6", "v7"});
        graph.build(obj);
        System.out.println(graph);

//        System.out.println(Arrays.toString(graph.shortPath(0)));
        System.out.println(Arrays.toString(graph.shortPathToStr(0)));
    }

}
