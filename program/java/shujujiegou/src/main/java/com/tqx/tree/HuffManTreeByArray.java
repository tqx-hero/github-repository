package com.tqx.tree;

import com.tqx.hash.HashMp;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 数组实现哈夫曼树
 * @date 2026/3/28 13:03
 */
public class HuffManTreeByArray<V> {

    static class ArrayHuffManTree<V> {
        double weight;
        V value;
        int parent, left, right;
//        BitSet code = new BitSet(1);

        @Override
        public String toString() {
            return "ArrayHuffManTree{" +
//                    "code=" + (code.get(0) ? 1 : 0) +
                    ", weight=" + weight +
                    ", value=" + value +
                    ", parent=" + parent +
                    ", left=" + left +
                    ", right=" + right +
                    '}';
        }

        public ArrayHuffManTree(V value, double weight) {
            this.value = value;
            this.weight = weight;
        }
    }


    ArrayHuffManTree<V>[] buildArray(Map<V, Double> map) {
        if (map == null || map.isEmpty())
            return new ArrayHuffManTree[]{};
        ArrayHuffManTree<V>[] trees = new ArrayHuffManTree[(map.size() << 1) - 1];
        PriorityQueue<Integer> queue = new PriorityQueue<>(
                Comparator.comparingDouble(s -> trees[s].weight)
        );
        int index = 0;
        for (Map.Entry entry : map.entrySet()) {
            trees[index] = new ArrayHuffManTree<>((V) entry.getKey(), (Double) entry.getValue());
            queue.add(index++);
        }
        //加入数组
        while (queue.size() > 1) {
            Integer i1 = queue.poll();
            Integer i2 = queue.poll();
            trees[index] = new ArrayHuffManTree<V>(null, trees[i1].weight + trees[i2].weight);
            trees[i1].parent = index;
            trees[i2].parent = index;
            trees[index].left = i1;
            trees[index].right = i2;
//            trees[i2].code.set(0);
            //添加新的index到队列
            queue.add(index++);
        }
        trees[trees.length - 1].parent = -1;
        return trees;
    }

    static Map<Character, Double> initMap() {
        Map<Character, Double> mp = new HashMap<>();
        mp.put('a', Double.valueOf(7));
        mp.put('b', Double.valueOf(5));
        mp.put('c', Double.valueOf(2));
        mp.put('d', Double.valueOf(4));
        return mp;
    }

    /**
     * 解码
     *
     * @param str
     * @param trees
     * @return
     */
    String decode(String str, ArrayHuffManTree<V>[] trees) {
        if (Objects.isNull(str) || str.length() == 0)
            return null;
        int rootIdx = trees.length - 1;
        char[] array = str.toCharArray();
        StringBuilder builder = new StringBuilder();
        for (int i = 0; i < array.length; i++) {
            rootIdx = array[i] == '0' ? trees[rootIdx].left : trees[rootIdx].right;
            V v = trees[rootIdx].value;
            if (v != null) {
                builder.append(v);
                rootIdx = trees.length - 1;
            }
        }
        return builder.toString();
    }

    private void encode(Map<V, String> resMap, ArrayHuffManTree<V>[] trees,
                        StringBuilder sb, int idx, V value) {
        //获取当前节点
        ArrayHuffManTree<V> leaf = trees[idx];
        //获取父节点
        if (leaf.parent == -1) {
            resMap.put(value, sb.reverse().toString());
            return;
        }
        ArrayHuffManTree<V> parentNode = trees[leaf.parent];
        sb.append(parentNode.left == idx ? '0' : '1');
        encode(resMap, trees, sb, leaf.parent, value);
    }

    Map<V, String> encode(ArrayHuffManTree<V>[] trees) {
        if (trees == null || trees.length == 0)
            return null;
        int maxIndex = ((trees.length + 1) >> 1) - 1;
        int begin = 0;
        Map<V, String> resMap = new HashMap<>();
        while (begin <= maxIndex) {
            StringBuilder sb = new StringBuilder();
            encode(resMap, trees, sb, begin, trees[begin++].value);
        }
        System.out.println(resMap);
        return resMap;
    }

    public static void main(String[] args) {
        Map<Character, Double> mp = new HashMap<>();
        mp.put('A', Double.valueOf(4));
        mp.put('S', Double.valueOf(2));
        mp.put('C', Double.valueOf(2));
        mp.put('T', Double.valueOf(3));
        mp.put(';', Double.valueOf(3));
//编码
        HuffManTreeByArray<Character> treeDemo = new HuffManTreeByArray<>();
        ArrayHuffManTree<Character>[] array = treeDemo.buildArray(mp);
        treeDemo.encode(array);
        //解码
        String str = "1011100";
        System.out.println(treeDemo.decode(str, array));
    }
//
//    public String getCode(Map<V, Double> map) {
////        HuffManTreeByArray<Character> treeDemo = new HuffManTreeByArray<>();
//        ArrayHuffManTree<V>[] trees = this.buildArray(map);
//
//    }

}
