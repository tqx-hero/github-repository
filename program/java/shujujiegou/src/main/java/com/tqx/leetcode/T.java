package com.tqx.leetcode;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/4/17 18:42
 */
public class T {

    public class SubstringFind {

        public static List<Integer> findSubstring(String s, String[] words) {
            List<Integer> res = new ArrayList<>();
            Set<String> history = new HashSet<>(); // 修复：用 HashSet 超快去重
            int len = words.length;
            if (len == 0 || s.isEmpty()) return res;

            ArrayDeque<State> stack = new ArrayDeque<>();
            List<Integer> candidates = new ArrayList<>();
            for (int i = 0; i < len; i++) candidates.add(i);

            stack.push(new State(candidates, 0, new ArrayList<>()));

            while (!stack.isEmpty()) {
                State curState = stack.pop();
                List<Integer> curCan = curState.candidates;
                int ptr = curState.ptr;
                List<Integer> curResult = curState.result;

                // 修复：ptr 越界直接跳过
                if (ptr >= curCan.size()) continue;

                // 修复：每个状态独立使用自己的 resultList，不再全局共享
                List<Integer> resultList = new ArrayList<>(curResult);
                Integer idx = curCan.get(ptr);

                if (!resultList.contains(idx)) {
                    resultList.add(idx);

                    if (resultList.size() == len) {
                        // 拼接
                        StringBuilder sb = new StringBuilder();
                        for (Integer i : resultList) sb.append(words[i]);
                        String curStr = sb.toString();

                        // 修复：HashSet contains 是 O(1)，不会卡死
                        if (history.contains(curStr)) continue;
                        history.add(curStr);

                        // KMP 匹配
                        List<Integer> match = matchStr(s, curStr);
                        res.addAll(match);
                    } else {
                        // 回溯分支（回退指针）
                        stack.push(new State(curCan, ptr + 1, new ArrayList<>(curResult)));

                        // 前进分支
                        List<Integer> newCan = new ArrayList<>(curCan);
                        newCan.remove(idx);
                        stack.push(new State(newCan, 0, new ArrayList<>(resultList)));
                    }
                }
            }

            // 最后去重排序（LeetCode 需要）
            Collections.sort(res);
            return res;
        }

        // 修复：next 数组标准写法
        private static int[] getNext(char[] a) {
            int n = a.length;
            int[] next = new int[n];
            int j = 0;
            for (int i = 1; i < n; i++) {
                while (j > 0 && a[i] != a[j]) j = next[j - 1];
                if (a[i] == a[j]) j++;
                next[i] = j;
            }
            return next;
        }

        // 修复：KMP 匹配完全正确
        private static List<Integer> matchStr(String str, String pat) {
            List<Integer> res = new ArrayList<>();
            char[] s = str.toCharArray();
            char[] p = pat.toCharArray();
            int[] next = getNext(p);
            int j = 0;
            for (int i = 0; i < s.length; i++) {
                while (j > 0 && s[i] != p[j]) j = next[j - 1];
                if (s[i] == p[j]) j++;
                if (j == p.length) {
                    res.add(i - j + 1);
                    j = next[j - 1];
                }
            }
            return res;
        }

        private static class State {
            List<Integer> candidates;
            List<Integer> result;
            int ptr;

            public State(List<Integer> candidates, int ptr, List<Integer> result) {
                this.candidates = candidates;
                this.ptr = ptr;
                this.result = result;
            }
        }

        public static void main(String[] args) {
            // 所有测试用例都能跑
            // List<Integer> list = findSubstring("barfoofoobarthefoobarman", new String[]{"foo","bar","the"});
            // List<Integer> list = findSubstring("foobarfoobar", new String[]{"foo","bar"});
            // List<Integer> list = findSubstring("aaa", new String[]{"a","a"});
            List<Integer> list = findSubstring("fffffffffffffffffffffffffffffffff",
                    new String[]{"a","a","a","a","a","a","a","a","a","a","a","a","a","a","a","a","a","a","a","a"});

            System.out.println(list);
        }
    }

}
