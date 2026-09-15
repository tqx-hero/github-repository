package com.example.test.graph;

import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.Array;
import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个图，以无向图为例
 * @date 2026/3/2 17:09
 */
public class Graph<E> {
    int arrSize = 10;  //顶点数量
    //    int numV;  //顶点的数量
    E[] arrV; //顶点列表
    int[][] edges;  //定义点与边的关系
    int numE;  //边的数量

    //    public Graph(E[] arrV, Class<T> type) {
    public Graph(E[] arrV) {
        this.arrV = arrV;
        arrSize = arrV.length;
        edges = new int[arrSize][arrSize];
//        edges = (T[][]) Array.newInstance(type, arrSize);
        initMatrix();
    }

    @Override
    public String toString() {
        return "Graph{" +
                "arrSize=" + arrSize +
                ", arrV=" + Arrays.toString(arrV) +
                ", edges=" + listArr() +
                ", numE=" + numE +
                '}';
    }


    private String listArr() {
        Arrays.stream(edges).forEach(e -> {
            Arrays.stream(e).forEach(System.out::println);
        });
        return "";
    }

    /**
     * 加载矩阵
     *
     * @param
     * @return
     */
    private Graph<E> initMatrix() {
        //加载矩阵,并设置点与自身的长度为0，与其他点默认长度为最大值
        for (int i = 0; i < arrV.length; i++) {
            for (int j = 0; j < arrV.length; j++) {
                if (i == j)
                    edges[i][j] = 0;
                edges[i][j] = Integer.MAX_VALUE;
            }
        }
        return this;
    }


    /**
     * 添加无向矩阵
     *
     * @param i
     * @param j
     * @param weight
     * @return
     */
    Graph<E> add(int i, int j, int weight) {
        if (i >= arrSize || j >= arrSize)
            return null;
        if (i == j)
            edges[i][j] = 0;
        else {
            edges[i][j] = weight;
            edges[j][i] = weight;
            numE++;
        }
        return this;
    }

    /**
     * 加载有向矩阵
     *
     * @param i
     * @param j
     * @param weight
     * @return
     */
    Graph<E> addHasDirection(int i, int j, int weight) {
        if (i >= arrSize || j >= arrSize)
            return null;
        if (i == j)
            edges[i][j] = 0;
        else {
            edges[i][j] = weight;
            numE++;
        }
        return this;
    }

    /**
     * 广度优先遍历图
     *
     * @param i
     */
    void listBreadth(int i) {
        if (i >= arrSize)
            return;
        boolean[] visiteds = new boolean[arrSize];
        visiteds[i] = true;
        GrapUsedArryQueue queue = new GrapUsedArryQueue();
        queue.add(new Entry(i, arrV[i]));
        listIByQueue(queue, visiteds);

    }

    class Entry {
        int idx;
        Object obj;

        public Entry(int idx, Object obj) {
            this.idx = idx;
            this.obj = obj;
        }
    }

    private void listIByQueue(GrapUsedArryQueue queue, boolean[] visiteds) {
        while (!queue.isEmpty()) {
            Entry obj = (Entry) queue.del();
            System.out.println(obj.obj);
            for (int k = 0; k < arrSize; k++) {
                if (edges[obj.idx][k] != 0 && edges[obj.idx][k] != Integer.MAX_VALUE && !visiteds[k]) {
                    visiteds[k] = true;
                    queue.add(new Entry(k, arrV[k]));
                }
            }
            listIByQueue(queue, visiteds);
        }
    }

    /**
     * 从某个节点开始深度遍历
     *
     * @param i
     */
    void listDepth(int i) {
        if (i >= arrSize)
            return;
        //设置每个顶点的访问状态
        listI(new GraphUserStack(), i, new boolean[arrSize]);
    }

    private void listI(GraphUserStack stack, int i, boolean[] visited) {
        if (!visited[i]) {
            visited[i] = true;
            stack.push(arrV[i]);
        }
        for (int j = 0; j < arrSize; j++) {
            if (edges[i][j] != 0 && edges[i][j] != Integer.MAX_VALUE) {
                if (!visited[j]) {
                    //放入入栈标志
                    visited[j] = true;
                    stack.push(arrV[j]);
                    listI(stack, j, visited);
                }
            }
        }
        System.out.println(stack.pop());
    }


//    String shortestPath(int i, int j) {
//
//    }

    void initTree() {
        //创建节点父节点对照表
        int[] parentIdx = new int[arrSize];
        //创建对应下标节点与树的权重，0为就在树内
        int[] distance = new int[arrSize];
        Arrays.fill(distance, Integer.MAX_VALUE);
        //设置树起点
        parentIdx[0] = 0;
        distance[0] = 0;
        //初始化并设置父节点与权重
        for (int j = 1; j < arrSize; j++) {
            distance[j] = edges[0][j];
            parentIdx[j] = 0;
        }
        createTree(parentIdx, distance, 0);
        System.out.println("树的下标=" + Arrays.toString(parentIdx));
        System.out.println("到树的距离=" + Arrays.toString(distance));
    }

    void createTree(int[] parentIdx, int[] distance, int begin) {

        //找到与起始点连接的顶点的最小值与下标

        for (int i = 1; i < arrSize; i++) {

            int findCIdx = 0;
            int minIDistance = Integer.MAX_VALUE;
            for (int j = 1; j < arrSize; j++) {
                if (distance[j] != 0 && distance[j] < minIDistance) {
                    minIDistance = distance[j];
                    findCIdx = j;
                }
            }
            distance[findCIdx] = 0;

            //更新与c相连的顶点
            for (int j = 1; j < arrSize; j++) {
                if (distance[j] != 0 && edges[findCIdx][j] < distance[j]) {
                    distance[j] = edges[findCIdx][j];
                    parentIdx[j] = findCIdx;
                }
            }
        }
    }


    public static void main(String[] args) {
        Graph<Character> graph = new Graph<>(new Character[]{'A', 'B', 'C', 'D', 'E', 'F'});
        graph.add(0, 1, 30)
                .add(0, 2, 200)
//                .add(0, 3, 300)
                .add(1, 2, 10)
                .add(1, 3, 40)
                .add(2, 4, 400)
                .add(2, 5, 1)
                .add(0, 4, 3);
        graph.initTree();
//        graph.listDepth(5);
//        graph.listBreadth(0);

    }

}
