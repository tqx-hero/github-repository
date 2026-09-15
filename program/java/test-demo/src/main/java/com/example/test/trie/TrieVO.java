package com.example.test.trie;

import java.util.Arrays;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 字典树
 * @date 2026/3/1 16:54
 */
public class TrieVO {

    static class TireNode {
        TireNode[] children = new TireNode[26];
        ; //下个节点的指针，通常为26个英文字母
        boolean isEnd = false;  //该节点是否结束
        char val;

        public TireNode() {
        }

        @Override
        public String toString() {
            return "TireNode{" +
                    "children=" + Arrays.toString(children) +
                    ", isEnd=" + isEnd +
                    ", val=" + val +
                    '}';
        }

        public TireNode(char val) {
            this.val = val;
        }
    }


    public final TireNode root;

    public TrieVO() {
        this.root = new TireNode();
    }

    public TireNode add(String word) {
        if (Objects.isNull(word)) return null;
        char[] chars = word.strip().toCharArray();
        TireNode rt = root;
        for (int i = 0; i < chars.length; i++) {
            int idx = chars[i] - 'a'; //计算新节点指针
            //查看树的对应指针下有无该节点，没有则创建新节点
            if (Objects.isNull(rt.children[idx])) {
                rt.children[idx] = new TireNode(chars[i]);
            }
            rt = rt.children[idx];
        }
        rt.isEnd = true;
        return root;
    }

    /**
     * 查看单词是否包括全路径
     *
     * @param word
     * @return
     */
    public boolean containAll(String word) {
        if (Objects.isNull(word)) return false;
        char[] array = word.strip().toCharArray();
        TireNode rt = root;
        for (int i = 0; i < array.length; i++) {
            int idx = array[i] - 'a';
            if (Objects.isNull(rt.children[idx])) return false;
            if (rt.children[idx].val == array[i])
                rt = rt.children[idx];
        }
        return rt.isEnd;
    }

    /**
     * 是否包含传入单词
     *
     * @param word
     * @return
     */
    public boolean contains(String word) {
        if (Objects.isNull(word)) return false;
        char[] array = word.strip().toCharArray();
        TireNode rt = root;
        for (int i = 0; i < array.length; i++) {
            int idx = array[i] - 'a';
            if (Objects.isNull(rt.children[idx])) return false;
            if (rt.children[idx].val == array[i])
                rt = rt.children[idx];
        }
        return true;
    }


    public static void main(String[] args) {
        TrieVO vo = new TrieVO();
        System.out.println(vo.add("word"));
        System.out.println(vo.containAll("wor"));
//        System.out.println(vo.contains("ww"));
    }

}
