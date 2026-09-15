package com.tqx.leetcode;

import java.util.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: 给定一个字符串 s 和一个字符串数组 words。 words 中所有字符串 长度相同。
 * <p>
 * s 中的 串联子串 是指一个包含  words 中所有字符串以任意顺序排列连接起来的子串。
 * <p>
 * 例如，如果 words = ["ab","cd","ef"]， 那么 "abcdef"， "abefcd"，"cdabef"， "cdefab"，"efabcd"， 和 "efcdab" 都是串联子串。 "acdbef" 不是串联子串，因为他不是任何 words 排列的连接。
 * 返回所有串联子串在 s 中的开始索引。你可以以 任意顺序 返回答案。
 * <p>
 * <p>
 * <p>
 * 示例 1：
 * <p>
 * 输入：s = "barfoothefoobarman", words = ["foo","bar"]
 * 输出：[0,9]
 * 解释：因为 words.length == 2 同时 words[i].length == 3，连接的子字符串的长度必须为 6。
 * 子串 "barfoo" 开始位置是 0。它是 words 中以 ["bar","foo"] 顺序排列的连接。
 * 子串 "foobar" 开始位置是 9。它是 words 中以 ["foo","bar"] 顺序排列的连接。
 * 输出顺序无关紧要。返回 [9,0] 也是可以的。
 * 示例 2：
 * <p>
 * 输入：s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
 * 输出：[]
 * 解释：因为 words.length == 4 并且 words[i].length == 4，所以串联子串的长度必须为 16。
 * s 中没有子串长度为 16 并且等于 words 的任何顺序排列的连接。
 * 所以我们返回一个空数组。
 * 示例 3：
 * <p>
 * 输入：s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
 * 输出：[6,9,12]
 * 解释：因为 words.length == 3 并且 words[i].length == 3，所以串联子串的长度必须为 9。
 * 子串 "foobarthe" 开始位置是 6。它是 words 中以 ["foo","bar","the"] 顺序排列的连接。
 * 子串 "barthefoo" 开始位置是 9。它是 words 中以 ["bar","the","foo"] 顺序排列的连接。
 * 子串 "thefoobar" 开始位置是 12。它是 words 中以 ["the","foo","bar"] 顺序排列的连接。
 * <p>
 * <p>
 * 提示：
 * <p>
 * 1 <= s.length <= 104
 * 1 <= words.length <= 5000
 * 1 <= words[i].length <= 30
 * words[i] 和 s 由小写英文字母组成
 * @date 2026/4/17 16:14
 */
public class Leetcode30 {

    //todo 未完成，该方法会超时，需要使用滑动窗口
    public static List<Integer> findSubstring(String s, String[] words) {
        List<Integer> res = new ArrayList<>();
        Set<String> history = new HashSet<>();
        int len = words.length;
        //压栈
        ArrayDeque<State> stack = new ArrayDeque<>();
//        List<Integer> resultList = new ArrayList<>();
        List<Integer> candidates = new ArrayList<>();
        for (int i = 0; i < len; i++)
            candidates.add(i);
        //压入初始数据
        stack.push(new State(candidates, 0, new ArrayList<>()));
        while (!stack.isEmpty()) {
            State curState = stack.pop();
            //加载当前数据
            List<Integer> curCan = curState.candidates;
            int ptr = curState.ptr;
            List<Integer> curResult = curState.result;
            if (curCan.size() <= ptr)
                continue;
            //恢复现场
            List<Integer> resultList = new ArrayList<>(curResult);

//            if (resultList.isEmpty()) {
//                resultList = new ArrayList<>(curResult);
//            }
//            if (!curCan.isEmpty()) {
            Integer idx = curCan.get(ptr);
            if (!resultList.contains(idx)) {
                resultList.add(idx);
                if (resultList.size() == len) {
                    //拼接字符串，进行KMP比较
                    StringBuilder sb = new StringBuilder();
                    for (Integer i : resultList)
                        sb.append(words[i]);
                    String curStr = sb.toString();
                    //清除结果集
                    resultList.clear();
                    //缓存一下字符串是否出现过，如果没出现则添加到缓存并进行匹配
                    //如果出现过，则直接忽略
                    if (history.contains(curStr))
                        continue;
                    history.add(curStr);
                    //KMP比较
                    List<Integer> r = matchStr(s, curStr);
                    if (!r.isEmpty())
                        res.addAll(r);
                } else {
                    //将回退状态压入栈内
                    if (curCan.size() > ptr + 1)
                        stack.push(new State(curCan, ptr + 1, new ArrayList<>(curResult)));
                    //压入前进状态
                    List<Integer> forwardCan = new ArrayList<>(curCan);
                    forwardCan.remove(idx);
                    if (!forwardCan.isEmpty())
                        stack.push(new State(forwardCan, 0, new ArrayList<>(resultList)));
                }

            }
//            }

        }
        return res;
    }

    //递推next数组
    private static int[] getNext(char[] a) {
        int len = a.length;
        int[] next = new int[len];
        //递推next数组
        if (len > 2) {
            for (var i = 2; i < len; i++) {
                int j;
                for (j = next[i - 1]; j != 0 && a[i - 1] != a[j]; j = next[j]) ;
                next[i] = a[i - 1] == a[j] ? j + 1 : 0;
            }
        }
        return next;
    }

    //字符串匹配KMP
    private static List<Integer> matchStr(String str, String s) {
        List<Integer> res = new ArrayList<>();
        char[] a = s.toCharArray();
        char[] sa = str.toCharArray();
        int len = s.length();
        //存放匹配失败时的最长前后缀相同的最后一个字符的next下标
        int[] next = getNext(a);
        //匹配，相同则同时移动指针，不同则回退k指针
        int k = 0, i;
        for (i = 0; i < sa.length; ) {
            if (k >= len) {
                //模式串到头了
                //记录开始的下标
                //同时重置正文串下标+1
                //模式串下标归零
                int idx = i - k;
                res.add(idx);
                i = idx + 1;
                k = 0;
                continue;
            }
            char c = sa[i];
            if (c == a[k]) {
                k++;
                i++;
            } else if (k == 0)
                i++;
            else
                k = next[k];
        }
        if (k >= len)
            res.add(i - k);
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
//        List<Integer> list = findSubstring("barfoofoobarthefoobarman", new String[]{"foo", "bar", "the"});
//        List<Integer> list = findSubstring("wordgoodgoodgoodbestword", new String[]{"word", "good", "best", "good"});
//        List<Integer> list = findSubstring("foobarfoobar", new String[]{"foo", "bar"});
        List<Integer> list = findSubstring("fffffffffffffffffffffffffffffffff", new String[]{"a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a", "a"});
//        List<Integer> list = findSubstring("aaa", new String[]{"a", "a"});
        System.out.println(list);
    }
}
