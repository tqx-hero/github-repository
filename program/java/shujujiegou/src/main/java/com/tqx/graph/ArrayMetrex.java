package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 矩阵构建的图
 * @date 2026/3/28 23:59
 */
public class ArrayMetrex {

    private static final double MAX_VAL = Double.MAX_VALUE - 1;

    static class Graph {
        private int[] visited;
        //加载顶点的数据
        Object[] vertexs;
        //定义边，即顶点之间的连通关系
        double[][] edges;
        int vs, es;

        public static boolean illegal(double weight) {
            return weight > 0 && weight < MAX_VAL;
        }

        @Override
        public String toString() {
            return "Graph{" +
                    "edges=" + Arrays.toString(edges) +
                    ", vertexs=" + Arrays.toString(vertexs) +
                    ", vs=" + vs +
                    ", es=" + es +
                    '}';
        }

        public Graph(int vs, int es) {
            this.es = es;
            this.vs = vs;
            this.vertexs = new Object[vs];
            edges = new double[vs][vs];
            this.visited = new int[vs];
        }

        public Graph(int vs) {
            this(vs, 0);
        }

        public Graph() {
        }

        public Integer getIndex(Object key) {
            for (int i = 0; i < vs; i++) {
                if (Objects.deepEquals(key, vertexs[i]))
                    return i;
            }
            return -1;
        }

        public void getEdges() {
            for (int i = 0; i < vs; i++) {
                for (int j = 0; j < vs; j++) {
                    System.out.println("edges [" + i + "][" + j + "]" + edges[i][j]);
                }

            }
        }

        /**
         * 初始化矩阵
         *
         * @param initValue 默认值
         */
        public void initGraph(Double initValue) {
            initValue = initValue == null ? MAX_VAL : initValue;
            for (int i = 0; i < vs; i++) {
                for (int j = 0; j < vs; j++) {
                    if (edges[i][j] == initValue)
                        continue;
                    edges[i][j] = initValue;
                    edges[j][i] = initValue;
                }
            }
        }

    }

    //传参形式： key:  a:b   value: num

    /**
     * 创建无向网
     *
     * @param vs
     * @param map
     * @return
     */
    Graph createGraph(Object[] vs, Map<String, Integer> map) {
        if (vs == null || vs.length == 0
                || Objects.isNull(map) || map.isEmpty())
            return null;
        //初始化图的顶点与它的edges
        Graph graph = new Graph(vs.length, map.size());
        graph.vertexs = Arrays.copyOf(vs, vs.length);
        double[][] edges = graph.edges;
        graph.initGraph(MAX_VAL);

        for (Map.Entry<String, Integer> entry : map.entrySet()) {
            String key = entry.getKey();
            String[] split = key.split(":");
            String a = split[0];
            String b = split[1];
            Integer value = entry.getValue();
            Integer ia = graph.getIndex(a);
            Integer ib = graph.getIndex(b);
            edges[ia][ib] = value;
            edges[ib][ia] = value;
        }
        return graph;
    }

    /**
     * 创建有向网
     *
     * @param vs
     * @param map
     * @return
     */
    Graph createDirectionGraph(Object[] vs, Map<String, Integer> map) {
        if (vs == null || vs.length == 0 || map == null || map.isEmpty())
            return null;
        Graph graph = new Graph(vs.length, map.size());
        graph.vertexs = Arrays.copyOf(vs, vs.length);
        //初始化数值
        graph.initGraph(MAX_VAL);
        map.entrySet().iterator().forEachRemaining(e -> {
            String key = e.getKey();
            Integer value = e.getValue();
            String[] split = key.split(":");
            String a = split[0];
            String b = split[1];
            graph.edges[graph.getIndex(a)][graph.getIndex(b)] = value;

        });
        return graph;
    }

    //深度优先遍历
    public void dfs(Graph graph, int index) {
        int max = graph.vs;
        int[] visited = graph.visited;
        Object[] os = graph.vertexs;
        double[][] edges = graph.edges;

        if (index < 0 || index >= max)
            return;
        ArrayDeque<Integer> deque = new ArrayDeque<>();
        //压栈
        deque.push(index);
        while (!deque.isEmpty()) {
            int pi = deque.pop();
            //跳过访问过的节点
            if (visited[pi] == 1)
                continue;

            System.out.println("当前元素：[" + os[pi] + "]");
            visited[pi] = 1;
            //逆序遍历，满足条件的入栈
            for (int i = max - 1; i >= 0; i--) {
                //直接跳过自身顶点检测，加速优化
                if (pi == i)
                    continue;
                double i1 = edges[pi][i];
                if (i1 > 0 && i1 < MAX_VAL && visited[i] == 0) {
                    deque.push(i);
                }
            }
        }
    }

    public void bfs(Graph graph, int index) {
        int total = graph.vs;
        Object[] vertexs = graph.vertexs;
        int[] visited = graph.visited;
        double[][] edges = graph.edges;
        if (index < 0 || index >= total)
            throw new IllegalArgumentException("输入的顶点下标必须在范围之内");
        ArrayDeque<Integer> queue = new ArrayDeque<>();
        queue.add(index);
        visited[index] = 1;
        while (!queue.isEmpty()) {
            int currentIndex = queue.poll();
            System.out.println("当前元素:[" + vertexs[currentIndex] + "]");
            for (int i = 0; i < total; i++) {
                double weight = edges[currentIndex][i];
                if (weight > 0 && weight < MAX_VAL && visited[i] == 0) {
                    queue.add(i);
                    visited[i] = 1;
                }
            }
        }
        //重置visited的数组
        Arrays.fill(visited, 0);
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
        Graph graph = metrex.createGraph(num, map);
        //深度优先
//        metrex.dfs(graph, 0);
        //广度优先
        metrex.bfs(graph, 0);
        //创建有向网
//        Graph graph = metrex.createDirectionGraph(num, map);
//        System.out.println(graph);
//        graph.getEdges();
//        graph.
    }

}
