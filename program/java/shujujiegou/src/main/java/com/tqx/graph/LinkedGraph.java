package com.tqx.graph;

import java.util.*;
import java.util.stream.IntStream;

/**
 * @author Administrator
 * @version 1.0
 * @description: 邻接表表示的图
 * @date 2026/3/29 8:41
 */
public class LinkedGraph {

    private static final int INIT_MAPPING_SIZE = 1 << 6;
    private static final String MAPPING_PREFIX = ":mc:";
    private int[] visited;
    private int verSize;
    private Object[] verValues;
    private GEntry[] entries;
    //数据对应关系
    private Map<Integer, Set<Integer>> valueMappings;
    private Map<String, Double> weightMappings;

    //邻接表的桶位，存放数据与第一个连接的指针信息
    private static class GEntry {
        Object value;
        ArcNode firstNode;

        @Override
        public String toString() {
            return "GEntry{" +
                    "firstNode=" + firstNode +
                    ", value=" + value +
                    '}';
        }

        public GEntry(Object value) {
            this.value = value;
        }
    }

    @Override
    public String toString() {
        return "LinkedGraph{" +
                "entries=" + Arrays.toString(entries) +
                ", visited=" + Arrays.toString(visited) +
                ", verSize=" + verSize +
                ", verValues=" + Arrays.toString(verValues) +
                ", valueMappings=" + valueMappings +
                ", weightMappings=" + weightMappings +
                '}';
    }

    //边的链表节点，存放顶点相连的边权重与点的坐标、下一个顶点的指针
    private static class ArcNode {
        double weight;
        int index;
        //该桶位Entry的下一个相连顶点的边
        ArcNode nextArc;

        @Override
        public String toString() {
            return "ArcNode{" +
                    "index=" + index +
                    ", weight=" + weight +
                    ", nextArc=" + nextArc +
                    '}';
        }

        public ArcNode(double weight) {
            this.weight = weight;
        }

        public ArcNode(int index, double weight) {
            this.index = index;
            this.weight = weight;
        }
    }

    public LinkedGraph(int verSize) {
        this.verSize = verSize;
        this.verValues = new Object[verSize];
        this.entries = new GEntry[verSize];
        this.visited = new int[verSize];
        this.valueMappings = new HashMap<>(INIT_MAPPING_SIZE);
        this.weightMappings = new HashMap<>(INIT_MAPPING_SIZE);
    }

    private void initGraph(Object[] objects) {
        verSize = objects.length;
        verValues = Arrays.copyOf(objects, verSize);
        for (int i = 0; i < verSize; i++) {
            entries[i] = new GEntry(verValues[i]);
        }
    }

    private int findIdx(Object key) {
        if (key == null) return -1;
        for (int i = 0; i < verSize; i++) {
            if (key.equals(verValues[i])) {
                return i;
            }
        }
        return -1;
    }


    private boolean isWeightEqual(Double w1, Double w2) {
        if (w1 == null && w2 == null)
            return true;
        if (w1 == null || w2 == null)
            return false;
        return Double.compare(w1, w2) == 0;
    }

    /**
     * 判断是否存在映射关系
     *
     * @param i1
     * @param i2
     * @param weight
     * @param compareWeight 是否比较权重，false则不进行比较
     * @return
     */
    private boolean containsMapping(Integer i1, Integer i2, Double weight, boolean compareWeight) {
        if (i1 == null || i2 == null || i1 < 0 || i2 < 0)
            return false;
        Set<Integer> set = valueMappings.get(i1);
        if (set == null || !set.contains(i2))
            return false;
        //判断权重是否相同
        if (!compareWeight)
            return true;
        String key = i1 + MAPPING_PREFIX + i2;
        Double v = weightMappings.get(key);
        return isWeightEqual(v, weight);
    }


    private void modifyMappingSet(Integer i1, Integer i2) {
        //如果没有就新建
        valueMappings.computeIfAbsent(i1, k -> new HashSet<>()).add(i2);
    }

    private void modifyWeightMappings(Integer i1, Integer i2, Double weight) {
        String key = i1 + MAPPING_PREFIX + i2;
        weightMappings.put(key, weight);
    }

    /**
     * 更新映射表
     *
     * @param i1
     * @param i2
     * @param weight
     * @param isOneWay 是否是单向表
     */
    private void updateMapping(Integer i1, Integer i2, Double weight, boolean isOneWay) {
        //更新权重weight
        modifyMappingSet(i1, i2);
        modifyWeightMappings(i1, i2, weight);
        if (!isOneWay) {
            modifyMappingSet(i2, i1);
            modifyWeightMappings(i2, i1, weight);
        }
    }

    private void modifyNodeWeight(ArcNode node, Integer i2, Double value) {
        ArcNode currentNode = node;
        while (currentNode != null) {
            if (node.index == i2) {
                node.weight = value;
                return;
            }
            currentNode = currentNode.nextArc;
        }
    }

    private void updateNodeVal(Integer i1, Integer i2, Double value) {
        GEntry entry = entries[i1];
        if (containsMapping(i1, i2, value, false)) {
            modifyNodeWeight(entry.firstNode, i2, value);
            return;
        }
        ArcNode s1Node = new ArcNode(i2, value);
        s1Node.nextArc = entry.firstNode;
        entry.firstNode = s1Node;

    }

    private void updateNode(Integer i1, Integer i2, Double value, boolean isOneWay) {
        updateNodeVal(i1, i2, value);
        if (!isOneWay) {
            updateNodeVal(i2, i1, value);
        }
    }


    /**
     * 加载无向图
     *
     * @param objects
     * @param map
     * @return
     */
    public LinkedGraph createGraph(Object[] objects, Map<String, Double> map) {
        if (objects == null || objects.length == 0 ||
                map == null || map.isEmpty())
            return this;
        //加载邻接表桶
        initGraph(objects);
        //添加边的链表
        for (Map.Entry<String, Double> entry : map.entrySet()) {
            String key = entry.getKey();
            Double value = entry.getValue();
            String[] split = key.split(":");
            String s1 = split[0];
            String s2 = split[1];
            int i1 = findIdx(s1);
            int i2 = findIdx(s2);
            if (i1 < 0 || i2 < 0) {
                System.err.println("顶点不存在：" + s1 + " <-> " + s2);
                continue;
            }
            if (!containsMapping(i1, i2, value, true)) {
                updateNode(i1, i2, value, false);
                //由于是无向图，所以需要维护这两个顶点的关系
                updateMapping(i1, i2, value, false);
            }
        }
        return this;
    }

    public void dfs(int begin) {
        int verSize = this.verSize;
        Object[] values = this.verValues;
        GEntry[] buckets = this.entries;
        int[] visited = this.visited;
        if (begin < 0 || begin >= verSize)
            throw new IllegalArgumentException("输入的下标越界");
        ArrayDeque<Integer> stack = new ArrayDeque<>();
        stack.push(begin);
        visited[begin] = 1;
        while (!stack.isEmpty()) {
            int currentIdx = stack.pop();
            System.out.println("当前元素:[" + values[currentIdx] + "]");
            GEntry entry = buckets[currentIdx];
            ArcNode currentNode = entry.firstNode;
            while (currentNode != null) {
                int index = currentNode.index;
                if (visited[index] == 0) {
                    stack.push(index);
                    visited[index] = 1;
                }
                currentNode = currentNode.nextArc;
            }
        }
        Arrays.fill(visited, 0);
    }

    /**
     * 遍历标准操作，比hashMap方式快
     *
     * @param begin
     */
    public void bfs(int begin) {
        int verSize = this.verSize;
        Object[] values = this.verValues;
        GEntry[] buckets = this.entries;
        int[] visited = this.visited;
        if (begin < 0 || begin >= verSize)
            throw new IllegalArgumentException("输入的下标越界");
        ArrayDeque<Integer> queue = new ArrayDeque<>();
        queue.add(begin);
        visited[begin] = 1;
        while (!queue.isEmpty()) {
            int currentIdx = queue.poll();
            System.out.println("当前元素:[" + values[currentIdx] + "]");
            GEntry entry = buckets[currentIdx];
            ArcNode currentNode = entry.firstNode;
            while (currentNode != null) {
                int index = currentNode.index;
                if (visited[index] == 0) {
                    queue.add(index);
                    visited[index] = 1;
                }
                currentNode = currentNode.nextArc;
            }
        }
        Arrays.fill(visited, 0);
    }

//    /**
//     * 广度优先
//     *
//     * @param begin
//     */
//    public void bfsNode(int begin) {
//        int verSize = this.verSize;
//        Object[] values = this.verValues;
//        Map<Integer, Set<Integer>> mappings = this.valueMappings;
//        int[] visited = this.visited;
//        if (begin < 0 || begin >= verSize)
//            throw new IllegalArgumentException("输入的下标越界");
//        if (mappings == null || mappings.isEmpty())
//            return;
//        ArrayDeque<Integer> queue = new ArrayDeque<>();
//        queue.add(begin);
//        visited[begin] = 1;
//        while (!queue.isEmpty()) {
//            int currentIdx = queue.poll();
//            System.out.println("当前元素：[" + values[currentIdx] + "]");
//            Set<Integer> set = mappings.get(currentIdx);
//            if (set == null || set.isEmpty())
//                continue;
//            for (Integer i : set) {
//                if (visited[i] == 0) {
//                    queue.add(i);
//                    visited[i] = 1;
//                }
//            }
//        }
//        Arrays.fill(visited, 0);
//    }

    public static void main(String[] args) {
        LinkedGraph graph = new LinkedGraph(5);
        String[] str = {"v1", "v2", "v3", "v4", "v5"};
        HashMap<String, Double> map = new HashMap<>();
        map.put("v1:v2", 10.00);
        map.put("v2:v1", 10.00);
//        map.put("v1:v3", 20.00);
        map.put("v2:v4", 5.00);
        map.put("v2:v5", 5.00);
        map.put("v5:v3", 5.00);
        map.put("v4:v3", 5.00);
        LinkedGraph linkedGraph = graph.createGraph(str, map);
//        System.out.println(linkedGraph);
        //广度优先
//        linkedGraph.bfs(0);
        //深度优先
        linkedGraph.dfs(0);
//        graph.verValues = new String[]{"a", "b", "c"};
//        System.out.println(graph.findIdx("c"));
    }
}
