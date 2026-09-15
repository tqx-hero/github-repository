package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 邻接多重表构造无向图
 * @date 2026/3/29 17:32
 */
public class MultiAdjacencyGraph {
    private static final String SUB_PREFIX = ":";
    private int arcNum;
    private int verNum;
    private Object[] valArr;
    private MultiGEntry[] buckets;
    private static final int INIT_MAPPING_SIZE = 1 << 6;
    private static final String MAPPING_PREFIX = ":mc:";
    //数据对应关系
    private Map<Integer, Set<Integer>> valueMappings;
    //由于是无向图，映射关系没有先后顺序，所以存储时需要让k1、k2的hashCode与verNum取模，
    // 按大小顺序排列放入，如：k1<k2 ,放入规则为 k1+MAPPING_PREFIX+k2
    //查询时同样先对k取模，按照顺序查询，这样一对映射只需要存储一条即可
    private Map<String, Double> weightMappings;

    @Override
    public String toString() {
        return "MultiAdjacencyGraph{" +
                "arcNum=" + arcNum +
                ", verNum=" + verNum +
                ", valArr=" + Arrays.toString(valArr) +
                ", buckets=" + Arrays.toString(buckets) +
                ", valueMappings=" + valueMappings +
                ", weightMappings=" + weightMappings +
                '}';
    }

    public MultiAdjacencyGraph(int verNum) {
        this.verNum = verNum;
        this.valArr = new Object[verNum];
        this.buckets = new MultiGEntry[verNum];
        this.valueMappings = new HashMap<>(INIT_MAPPING_SIZE);
        this.weightMappings = new HashMap<>(INIT_MAPPING_SIZE);
    }

    static class MultiGEntry {
        MultiGNode firstNode;
        Object value;

        @Override
        public String toString() {
            return "MultiGEntry{" +
                    "firstNode=" + firstNode +
                    ", value=" + value +
                    '}';
        }

        public MultiGEntry(Object value) {
            this.value = value;
        }
    }

    static class MultiGNode {
        @Override
        public String toString() {
            return "MultiGNode{" +
                    "headIdx=" + iIdx +
                    ", weight=" + weight +
                    ", tailIdx=" + jIdx +
                    ", headNext=" + iNext +
                    ", tailNext=" + jNext +
                    '}';
        }

        //数据，备用
//        Object mask;
        double weight;
        int iIdx;
        int jIdx;
        MultiGNode iNext;
        MultiGNode jNext;

        public MultiGNode(double weight) {
            this.weight = weight;
        }
    }

    private void initGraph(Object[] arr) {
        valArr = Arrays.copyOf(arr, verNum);
        for (int i = 0; i < verNum; i++)
            buckets[i] = new MultiGEntry(valArr[i]);
    }

    private int findIdx(String str) {
        if (str == null || str.isEmpty())
            return -1;
        for (int i = 0; i < valArr.length; i++) {
            if (valArr[i].equals(str))
                return i;
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

    //更新节点的指针
    private void updateInNode(Integer i1, Integer i2, MultiGNode node) {
        MultiGEntry inEntry = buckets[i1];
        MultiGNode firstInNode = inEntry.firstNode;
        node.jIdx = i2;
        node.jNext = firstInNode;
        inEntry.firstNode = node;
    }


    private void updateNode(Integer i1, Integer i2, Double value) {
        MultiGEntry entry = buckets[i1];
        if (containsMapping(i1, i2, value, false)) {
            modifyNodeWeight(entry.firstNode, i2, value);
            return;
        }
        //新建节点
        MultiGNode s1Node = new MultiGNode(value);
        s1Node.iNext = entry.firstNode;
        s1Node.iIdx = i2;
        entry.firstNode = s1Node;
        //更新i2的节点
        updateInNode(i2, i1, s1Node);
        arcNum++;
    }

    void modifyNodeWeight(MultiGNode node, Integer i2, Double value) {
        MultiGNode currentNode = node;
        while (currentNode != null) {
            if (node.iIdx == i2) {
                node.weight = value;
                return;
            }
            currentNode = currentNode.iNext;
        }
    }

    private boolean containsMapping(Integer i1, Integer i2, Double weight, boolean compareWeight) {
        if (i1 == null || i2 == null || i1 < 0 || i2 < 0)
            return false;
        Set<Integer> set = valueMappings.get(i1);
        if (set == null || !set.contains(i2))
            return false;
        //判断权重是否相同
        if (!compareWeight)
            return true;
        //分别对i1和i2与表长度取模，顺序排列
        if (i1 > i2) {
            i1 = i1 ^ i2;
            i2 = i1 ^ i2;
            i1 = i1 ^ i2;
        }
        String key = i1 + MAPPING_PREFIX + i2;
        Double v = weightMappings.get(key);
        return isWeightEqual(v, weight);
    }

    void modifyMappingSet(Integer i1, Integer i2) {
        //如果没有就新建
        valueMappings.computeIfAbsent(i1, k -> new HashSet<>()).add(i2);
    }

    void modifyWeightMappings(Integer i1, Integer i2, Double weight) {
        if (i1 > i2) {
            i1 = i1 ^ i2;
            i2 = i1 ^ i2;
            i1 = i1 ^ i2;
        }
        String key = i1 + MAPPING_PREFIX + i2;
        weightMappings.put(key, weight);
    }

    /**
     * 更新映射表
     *
     * @param i1
     * @param i2
     * @param weight
     */
    private void updateMapping(Integer i1, Integer i2, Double weight) {
        //更新权重weight
        modifyMappingSet(i1, i2);
        modifyWeightMappings(i1, i2, weight);
    }

    public MultiAdjacencyGraph createGraph(Object[] arr, Map<String, Double> map) {
        if (arr == null || arr.length == 0 ||
                map == null || map.isEmpty())
            return this;
        initGraph(arr);
        for (Map.Entry<String, Double> entry : map.entrySet()) {
            String key = entry.getKey();
            String[] split = key.split(SUB_PREFIX);
            String s1 = split[0];
            String s2 = split[1];
            int i1 = findIdx(s1);
            int i2 = findIdx(s2);
            if (i1 == -1 || i2 == -1) {
                System.err.println("顶点不存在：" + i1 + " <-> " + i2);
                continue;
            }
            Double v = entry.getValue();

            if (!containsMapping(i1, i2, v, true)) {
                updateNode(i1, i2, v);
                updateMapping(i1, i2, v);
            }
        }
        return this;
    }


    public static void main(String[] args) {
        MultiAdjacencyGraph graph = new MultiAdjacencyGraph(5);
        String[] str = {"v1", "v2", "v3", "v4", "v5"};
        HashMap<String, Double> map = new HashMap<>();
        map.put("v1:v2", 10.00);
        map.put("v2:v1", 10.00);
        map.put("v1:v3", 20.00);
        map.put("v2:v4", 5.00);
        map.put("v2:v5", 5.00);
        map.put("v5:v3", 5.00);
        map.put("v4:v3", 5.00);
        map.put("v4:v3", 5.00);
        System.out.println(graph.createGraph(str, map));
//        graph.verValues = new String[]{"a", "b", "c"};
//        System.out.println(graph.findIdx("c"));
    }

}
