package com.tqx.tree;


import com.tqx.hash.HashMp;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 链表构建哈夫曼树
 * @date 2026/3/28 11:17
 */
public class HuffManTreeDemo<V> {

    static class HuffManTree<V> {
        double weight;
        V value;
        HuffManTree<V> left;
        HuffManTree<V> right;

        public HuffManTree(HuffManTree<V> left, HuffManTree<V> right, double weight, V value) {
            this.left = left;
            this.right = right;
            this.weight = weight;
            this.value = value;
        }

        @Override
        public String toString() {
            return "HuffManTree{" +
                    "left=" + left +
                    ", weight=" + weight +
                    ", value=" + value +
                    ", right=" + right +
                    '}';
        }

        public HuffManTree() {
        }

        public HuffManTree(V value, double weight) {
            this.value = value;
            this.weight = weight;
        }

        public HuffManTree<V> setWeight(double weight) {
            this.weight = weight;
            return this;
        }

        public HuffManTree(V value) {
            this.value = value;
        }
    }

    static Map<Character, Double> initMap() {
        Map<Character, Double> mp = new HashMap<>();
        mp.put('A', Double.valueOf(4));
        mp.put('S', Double.valueOf(2));
        mp.put('C', Double.valueOf(2));
        mp.put('T', Double.valueOf(3));
        mp.put(';', Double.valueOf(3));
        return mp;
    }


    HuffManTree<V> bulidHuffManTree(Map<V, Double> map) {
        if (map == null)
            return null;
        PriorityQueue<HuffManTree> queue = new PriorityQueue<>(Comparator.comparingDouble(h -> h.weight));
        map.forEach((k, v) ->
                queue.add(new HuffManTree<>(k, v))
        );
        for (; queue.size() > 1; ) {
            HuffManTree h1 = queue.poll();
            HuffManTree h2 = queue.poll();
            queue.add(new HuffManTree<>(h1, h2, h1.weight + h2.weight, null));
        }
        return queue.poll();
    }


    //1101000

//    A的编码:100
//    C的编码:101
//    S的编码:11
//    T的编码:00
//    ;的编码:01

    String decode(String charStr, HuffManTree<V> tree) {
        HuffManTree<V> t = tree;
        StringBuilder builder = new StringBuilder();
        for (char c : charStr.toCharArray()) {
            t = c == '0' ? t.left : t.right;
            if (t != null && t.value != null) {
                builder.append(t.value);
                t = tree;
            }
        }
        return builder.toString();
    }

    public static void main(String[] args) {
//        Map<Character, Double> mp = new HashMap<>();
//        mp.put('a', Double.valueOf(7));
//        mp.put('b', Double.valueOf(5));
//        mp.put('c', Double.valueOf(2));
//        mp.put('d', Double.valueOf(4));
//编码
        HuffManTreeDemo<Character> treeDemo = new HuffManTreeDemo<>();
//        System.out.println(treeDemo.bulidHuffManTree(mp));
        Map<Character, Double> map = initMap();
        treeDemo.getCode(map);

        //解码
//        HuffManTree<Character> tree = treeDemo.bulidHuffManTree(map);
//        treeDemo.getCode(map);
//        Map<Character, String> hashMap = new HashMap<>();
//        String str = "1011100";
//        System.out.println(treeDemo.decode(str, tree));
//        treeDemo.encode(tree, new StringBuilder(), hashMap);
    }

    void encode(HuffManTree<V> tree, StringBuilder sb, Map<V, String> code) {
        if (Objects.isNull(tree))
            return;
        if (tree.left == null && tree.right == null) {
            code.put(tree.value, sb.toString());
            return;
        }
        //往左走
        sb.append('0');
        encode(tree.left, sb, code);
        sb.deleteCharAt(sb.length() - 1);
        //往右走
        sb.append('1');
        encode(tree.right, sb, code);
        sb.deleteCharAt(sb.length() - 1);
    }

    //
    public String getCode(Map<V, Double> map) {
        HuffManTree<V> tree = this.bulidHuffManTree(map);
        Map<V, String> hashMap = new HashMap<>();
        encode(tree, new StringBuilder(), hashMap);
        hashMap.forEach((k, v) ->
                System.out.println(k + "的编码:" + v)
        );
        return null;
    }


}
