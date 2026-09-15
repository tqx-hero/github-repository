package com.example.test.trie;

import com.example.test.heap.BigHeap;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 力扣820题：
 * 构造最短字符串S，包含所有单词（#结尾）
 * 规则：如果A是B的后缀，A可以藏在B里面，不用单独写。
 * 例如：["time","me","bell"]
 * 1、me是time后缀，合并为： "time#"
 * 2、bell无后缀关系->单独为"bell#"
 * <p>
 * 解题思路：
 * 字典树可以查询字符串的包含关系，所以这里用到字典树，但是这里是后缀匹配，字典树是前置匹配，所以这里需要将字符串翻转过来，
 * 将数组中字符串全部录入，录入完挨个比对，全路径匹配的返回，否则不要
 * 返回时注意把字符串翻转回来
 * @date 2026/3/1 18:55
 */
public class LeetCode820 {

    static int ans = 0;

    static void dfs(TrieVO.TireNode vo, int depth) {
        boolean isLeaf = true;
        //深度遍历，统计叶子节点个数 ,这里26是指每个父节点最大可能的子节点数量，26个英文字母
        for (int i = 0; i < 26; i++) {
            if (Objects.nonNull(vo.children[i])) {
                isLeaf = false;
                dfs(vo.children[i], depth + 1);
            }
        }
        if (isLeaf && depth > 0) {
            ans += (depth + 1);
        }
    }

    public static int init(String[] str) {
        if (Objects.isNull(str) || str.length == 0) return 0;
        TrieVO vo = new TrieVO();
//        BigHeap
        //翻转字符串,录入字典树
        for (int i = 0; i < str.length; i++) {
            str[i] = new StringBuilder(str[i]).reverse().toString();
            vo.add(str[i]);
        }
        dfs(vo.root, 0);
        return ans;
    }

    public static void main(String[] args) {
        System.out.println(init(new String[]{"time", "me", "bell", "timer"}));


    }

}
