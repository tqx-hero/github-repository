package com.tqx.graph;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 十字链表：解决有向图的找出度易，入度难的弧问题
 * @date 2026/3/29 15:48
 */
public class CrossLinkedGraph {

    private static final int INIT_MAPPING_SIZE = 1 << 6;
    private static final String MAPPING_PREFIX = ":mc:";
    private static final String SUB_PREFIX = ":";
    private int arcNum;
    private int verNum;
    private Object[] verVals;
    private GCEntry[] entryArray;
    private Map<String, Double> weightMappings;
    private Map<Integer, Set<Integer>> outMappings;
    private Map<Integer, Set<Integer>> inMappings;

    @Override
    public String toString() {
        return "CrossLinkedGraph{" +
                "arcNum=" + arcNum +
                ", verNum=" + verNum +
                ", verVals=" + Arrays.toString(verVals) +
                ", entryArray=" + Arrays.toString(entryArray) +
                ", weightMappings=" + weightMappings +
                ", outMappings=" + outMappings +
                ", inMappings=" + inMappings +
                '}';
    }

    //桶位的节点
    static class GCEntry {
        //出度的弧
        CrossLinkedNode firstOutNode;
        //入度狐
        CrossLinkedNode firstInNode;
        Object value;

        @Override
        public String toString() {
            return "GCEntry{" +
                    "firstInNode=" + firstInNode +
                    ", firstOutNode=" + firstOutNode +
                    ", value=" + value +
                    '}';
        }

        public GCEntry(Object value) {
            this.value = value;
        }
    }

    //链表节点
    static class CrossLinkedNode {
        double weight;
        int tailIdx;
        int headIdx;
        CrossLinkedNode headNext;
        CrossLinkedNode tailNext;

        public CrossLinkedNode(double weight) {
            this.weight = weight;
        }

        @Override
        public String toString() {
            return "CrossLinkedNode{" +
                    "headIdx=" + headIdx +
                    ", weight=" + weight +
                    ", tailIdx=" + tailIdx +
                    ", headNext=" + headNext +
                    ", tailNext=" + tailNext +
                    '}';
        }
    }

    public CrossLinkedGraph(int verNum) {
        this.verNum = verNum;
        this.verVals = new Object[verNum];
        this.entryArray = new GCEntry[verNum];
        this.outMappings = new HashMap<>(INIT_MAPPING_SIZE);
        this.inMappings = new HashMap<>(INIT_MAPPING_SIZE);
        this.weightMappings = new HashMap<>(INIT_MAPPING_SIZE);
    }

    private int findIdx(String str) {
        if (str == null || str.isEmpty())
            return -1;
        for (int i = 0; i < verVals.length; i++) {
            if (verVals[i].equals(str))
                return i;
        }
        return -1;
    }

    private void initGraph(Object[] verArr) {
        verVals = Arrays.copyOf(verArr, verNum);
        for (int i = 0; i < verNum; i++) {
            entryArray[i] = new GCEntry(verVals[i]);
        }
    }

    private void modifyOutMappingSet(Integer i1, Integer i2) {
        //如果没有就新建
        outMappings.computeIfAbsent(i1, k -> new HashSet<>()).add(i2);
    }

    private void modifyWeightMappings(Integer i1, Integer i2, Double weight) {
        String key = i1 + MAPPING_PREFIX + i2;
        weightMappings.put(key, weight);
    }

    private void modifyInMappingSet(Integer i1, Integer i2) {
        inMappings.computeIfAbsent(i1, k -> new HashSet<>()).add(i2);
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
        modifyOutMappingSet(i1, i2);
        modifyInMappingSet(i2, i1);
        modifyWeightMappings(i1, i2, weight);
    }

    private void modifyNodeWeight(CrossLinkedNode node, Integer i2, Double value) {
        CrossLinkedNode currentNode = node;
        while (currentNode != null) {
            if (node.headIdx == i2) {
                node.weight = value;
                return;
            }
            currentNode = currentNode.headNext;
        }
    }

    //更新入度节点的firstInNode指针
    private void updateInNode(Integer i1, Integer i2, CrossLinkedNode node) {
        GCEntry inEntry = entryArray[i1];
        CrossLinkedNode firstInNode = inEntry.firstInNode;
        node.tailIdx = i2;
        node.tailNext = firstInNode;
        inEntry.firstInNode = node;
    }


    private void updateNode(Integer i1, Integer i2, Double value) {
        GCEntry entry = entryArray[i1];
        if (containsMapping(i1, i2, value, false)) {
            modifyNodeWeight(entry.firstOutNode, i2, value);
            return;
        }
        //新建节点，添加后维护出度的头顶点的firstInNode
        CrossLinkedNode s1Node = new CrossLinkedNode(value);
        s1Node.headNext = entry.firstOutNode;
        s1Node.headIdx = i2;
        entry.firstOutNode = s1Node;
        //更新i2的入度信息
        updateInNode(i2, i1, s1Node);
        arcNum++;
    }

    private boolean isWeightEqual(Double w1, Double w2) {
        if (w1 == null && w2 == null)
            return true;
        if (w1 == null || w2 == null)
            return false;
        return Double.compare(w1, w2) == 0;
    }

    private boolean containsMapping(Integer i1, Integer i2, Double weight, boolean compareWeight) {
        if (i1 == null || i2 == null || i1 < 0 || i2 < 0)
            return false;
        Set<Integer> set = outMappings.get(i1);
        if (set == null || !set.contains(i2))
            return false;
        //判断权重是否相同
        if (!compareWeight)
            return true;
        String key = i1 + MAPPING_PREFIX + i2;
        Double v = weightMappings.get(key);
        return isWeightEqual(v, weight);
    }

    public CrossLinkedGraph createCrossLinkedGraph(Object[] verArr, Map<String, Double> map) {
        if (verArr == null || verArr.length == 0 ||
                map == null || map.isEmpty())
            return this;
        initGraph(verArr);
        for (Map.Entry<String, Double> entry : map.entrySet()) {
            String k = entry.getKey();
            String[] arr = k.split(SUB_PREFIX);
            String k1 = arr[0];
            String k2 = arr[1];
            int i1 = findIdx(k1);
            int i2 = findIdx(k2);
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
        CrossLinkedGraph graph = new CrossLinkedGraph(5);
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
        System.out.println(graph.createCrossLinkedGraph(str, map));
//        graph.verValues = new String[]{"a", "b", "c"};
//        System.out.println(graph.findIdx("c"));
    }

}
