package com.tqx.graph;

import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: AOE网求关键路径
 * @date 2026/4/2 17:36
 */
@Deprecated
public class KeyPath_Dep {

    private Object[] vObj;
    private String[] edgName;
    private int keyPathVal;
    //分别为
    // 1、顶点最早开始的时间 ve = 从起始节点到该节点最长路径
    //2、顶点最晚开始时间 vl = 关键路径-  从最终节点到该顶点的最长路径
    //3、任务（路径，也就是边）最早开始时间, = 弧尾节点的ve
    //4、任务（路径，也就是边）最晚开始的时间 =  弧头最晚开始时间-路径长度
    //最后计算al、ae，两者相减=0的，则为关键路径
    private double[] ve, vl, ae, al;


    static class MaxPathNode {
        int index;
        double weight;

        @Override
        public String toString() {
            return "MaxPathNode{" +
                    "index=" + index +
                    ", weight=" + weight +
                    '}';
        }

        public MaxPathNode(int index, double weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    static class kGraph {
        private GNode[] buckets;
        private int vs;
        private Object[] vObj;
        private String[] arcArr;
        private ArcNode[] arcMapping;
        private int edgeNum;

        @Override
        public String toString() {
            return "kGraph{" +
                    "arcArr=" + Arrays.toString(arcArr) +
                    ", buckets=" + Arrays.toString(buckets) +
                    ", vs=" + vs +
                    ", vObj=" + Arrays.toString(vObj) +
                    ", arcMapping=" + Arrays.toString(arcMapping) +
                    ", edgeNum=" + edgeNum +
                    '}';
        }

        static class GNode {
            Object val;
            //连接的是与节点相连的所有弧头
            ArcNode firstNode;

            public GNode(Object val) {
                this.val = val;
            }

            @Override
            public String toString() {
                return "GNode{" +
                        "firstNode=" + firstNode +
                        ", val=" + val +
                        '}';
            }
        }

        //定义边
        static class ArcNode {
            //弧头节点
            int headIndex;
            //弧尾节点
            int tailIndex;
            double weight;
            ArcNode next;
            String arcName;

            @Override
            public String toString() {
                return "ArcNode{" +
                        "arcName='" + arcName + '\'' +
                        ", headIndex=" + headIndex +
                        ", tailIndex=" + tailIndex +
                        ", weight=" + weight +
                        ", next=" + next +
                        '}';
            }

            public ArcNode(int headIndex, int tailIndex, double weight, String arcName) {
                this.arcName = arcName;
                this.headIndex = headIndex;
                this.tailIndex = tailIndex;
                this.weight = weight;
            }
        }

        private void init(Object[] v, int length) {
            this.vs = v.length;
            edgeNum = length;
            buckets = new GNode[vs];
            vObj = Arrays.copyOf(v, vs);
            arcArr = new String[length];
            arcMapping = new ArcNode[length];
            for (int i = 0; i < vs; i++) {
                buckets[i] = new GNode(vObj[i]);
            }
        }

        // [[1,2,3],[3,2,6]]
        public kGraph createGraph(Object[] v, Object[][] edges) {
            if (v == null || v.length == 0 || edges == null
                    || edges.length == 0)
                return this;
            init(v, edges.length);
            for (int i = 0; i < edges.length; i++) {
                Object[] edge = edges[i];
                int i1 = (int) edge[0];
                int i2 = (int) edge[1];
                double weight = (double) (Integer) edge[2];
                String arcName = (String) edge[3];
                ArcNode firstNode = buckets[i1].firstNode;
                ArcNode currentNode = new ArcNode(i2, i1, weight, arcName);
                arcArr[i] = arcName;
                arcMapping[i] = currentNode;
                currentNode.next = firstNode;
                buckets[i1].firstNode = currentNode;
            }
            return this;
        }
    }

    //关键路径
    //先计算每个顶点的距离ve 找出关键路径的长度
    //
    public String[] keyPath(kGraph kGraph, int begin, int end) {
        //1、
        return null;
    }

    private static final double MAX_WEIGHT = Double.MIN_VALUE;

    //计算从begin开始到各顶点最长距离
    private double[] calculate(kGraph graph, int begin) {
        //迪杰斯特拉算法，计算最大值
        PriorityQueue<MaxPathNode> maxHeap = new PriorityQueue<>((a, b) ->
                Double.compare(b.weight, a.weight));
        kGraph.GNode[] buckets = graph.buckets;
        this.vObj = graph.vObj;
        int size = graph.vs;
        double[] maxLen = new double[size];
        Arrays.fill(maxLen, MAX_WEIGHT);
        this.edgName = graph.arcArr;
        kGraph.ArcNode[] arcMapping = graph.arcMapping;
        maxHeap.add(new MaxPathNode(begin, 0));
        boolean[] visited = new boolean[size];
        while (!maxHeap.isEmpty()) {
            MaxPathNode pathNode = maxHeap.poll();
            int index = pathNode.index;
            if (visited[index])
                continue;
            kGraph.GNode node = buckets[index];
            kGraph.ArcNode arcNode = node.firstNode;
            if (arcNode == null)
                break;
            double weight = arcNode.weight;
            maxLen[index] = weight;
            visited[index] = true;
            while (arcNode != null) {
                kGraph.ArcNode next = arcNode.next;
                if (next == null)
                    break;
                double w1 = next.weight;
                double v = weight + w1;
                //todo unfinished
//                if (v > maxLen[next.])
            }
        }
        return null;
    }

    public static kGraph getGraph() {
        String[] obj = {"V1", "V2", "V3", "V4", "V5", "V6", "V7", "V8", "V9"};
        Object[][] edges = {
                {0, 1, 6, "a1"},    //a1
                {0, 2, 4, "a2"},    //a2
                {0, 3, 5, "a3"},    //a3
                {1, 4, 1, "a4"},    //a4
                {2, 4, 1, "a5"},    //a5
                {3, 5, 2, "a6"},    //a6
                {4, 6, 9, "a7"},    //a7
                {4, 7, 7, "a8"},    //a8
                {5, 7, 4, "a9"},    //a9
                {6, 8, 2, "a10"},    //a10
                {7, 8, 4, "a11"}    //a11
        };
        kGraph graph = new kGraph();
        return graph.createGraph(obj, edges);
    }

    public static void main(String[] args) {
        kGraph kGraph = KeyPath_Dep.getGraph();
        System.out.println(kGraph);
    }

}
