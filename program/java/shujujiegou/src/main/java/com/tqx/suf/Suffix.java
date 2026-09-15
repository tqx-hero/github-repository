package com.tqx.suf;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 后缀数组
 * @date 2026/4/20 18:03
 */
public class Suffix {

    static class SuffixNode implements Comparable<SuffixNode> {
        int index;
        String suffix;

        public SuffixNode(int index, String suffix) {
            this.index = index;
            this.suffix = suffix;
        }

        @Override
        public String toString() {
            return "SuffixNode{" +
                    "index=" + index +
                    ", suffix='" + suffix + '\'' +
                    '}';
        }

        @Override
        public int compareTo(SuffixNode o) {
            return this.suffix.compareTo(o.suffix);
        }
    }

    public static SuffixNode[] getRank(String str) {
        SuffixNode[] a = new SuffixNode[str.length()];
        for (int i = 0; i < str.length(); i++)
            a[i] = new SuffixNode(i, str.substring(i));
        Arrays.sort(a);
        return a;
    }

    static class SaNode {
        Integer[] sa;
        int[] rank;

        @Override
        public String toString() {
            return "SaNode{" +
                    "rank=" + Arrays.toString(rank) +
                    ", sa=" + Arrays.toString(sa) +
                    '}';
        }

        public SaNode(int[] rank, Integer[] sa) {
            this.rank = rank;
            this.sa = sa;
        }
    }

    //求解后缀数组sa[]与它的排名rank[]
    public static SaNode getRankArr(String str) {
        int len = str.length();
        Integer[] sa = new Integer[len];
        int[] rank = new int[len];
        int[] temp = new int[len];
        //将子串的起始下标装入后缀数组
        for (int i = 0; i < len; i++)
            sa[i] = i;
        //比较规则：
        //倍增法，每次仅比较这一个字符
        //这样就等同于整型的数组比较
        for (int k = 1; k < len; k <<= 1) {
            int[] finalRank = rank;
            int gap = k >>> 1;
            //todo 这里可以换成用基数排序实现
            Arrays.sort(sa, (x, y) -> {
                //每次比较一个字符
                //第一次首字母比较 i+0
                //第二次比较 i+1,第三次i+2,i+4,i+8，直到倍增数量k超过字符串总长
                //第一次进来首字母比较
                if (gap == 0)
                    return Character.compare(str.charAt(x), str.charAt(y));
                //如果kk不为0，说明之前比较过，那就用rank比较
                if (finalRank[x] != finalRank[y])
                    return finalRank[x] - finalRank[y];
                //如果rank相同，那就比较倍增后的字符
                //判断倍增后的那个字符有没有越界
                //有越界的，下标越小的串越长，排名越靠后,直接下标相减取反
                if (x + gap >= len || y + gap >= len)
                    return -(x - y);
                //如果都没有越界，直接让它们倍增后的字符所在的那个子串进行rank比较
                return finalRank[x + gap] - finalRank[y + gap];
            });
            //一轮排序过后，将统计结果装入rank(桶)
            //rank用于记录这轮字符排名
            temp[sa[0]] = 0;
            int c = 1;
            for (int i = 1; i < len; i++) {
                //比较当前比较的字符是否与前一个相同
                //相同则装入同一个rank内
                //先判断下标有没有越界，
                // 越界的话直接按照当前排序入桶
                //没有越界就需要查看字符是否相同，
                // 相同就与前一位入同一个桶
                //不相同入当前桶
                temp[sa[i]] = sa[i] + gap >= len || sa[i - 1] + gap >= len ?
                        c++ :
                        rank[sa[i]] != rank[sa[i - 1]] ? c++ :
                                (str.charAt(sa[i] + gap) == str.charAt(sa[i - 1] + gap) ? c - 1 : c++);
            }
            //将该轮结果放到rank集以备下轮排序使用
            rank = Arrays.copyOf(temp, len);
            //当c与字符串长度相同，代表rank排名已定
            //后缀数组生成，直接退出
            if (c == len)
                break;
        }
        //完成排序后统计rank
        for (int i = 0; i < len; i++) {
            rank[sa[i]] = i;
        }
        return new SaNode(rank, sa);
    }

    //通过rank与后缀数组sa计算最长公共前缀lcp[]
    //数组记录的是下标从0开始的后缀子串所拥有的最长公共前缀长度LCP
    public static int[] getLCP(SaNode node, String str) {
        int len = str.length();
        Integer[] sa = node.sa;
        int[] rank = node.rank;
        int[] lcp = new int[len];
        for (int i = 0; i < len; i++) {
            if (i != 0 && lcp[i - 1] != 0) {
                // todo 长度不为0，直接返回-1，这里是否应该再次从k-1比较?
                lcp[i] = lcp[i - 1] - 1;
                continue;
            }
            //通过rank找到子串所在的后缀数组位置
            int saI = rank[i];
            //下标为0的，说明这个子串最短，直接设置0
            if (saI == 0) {
                lcp[i] = 0;
                continue;
            }
            //所在后缀数组下标不为0,
            //比较它与前面的字符串
            //查看前面的这个子串后缀长度是否为0
            int curI = sa[saI];
            Integer preI = sa[saI - 1];
            int count;
            //从头开始遍历匹配
            //匹配字符串，同时记录count
            //不匹配时直接退出
            for (count = 0; curI < len && preI < len && str.charAt(curI) == str.charAt(preI); curI++, preI++, count++) ;
            //退出后记录count为最长公共前缀
            lcp[i] = count;
        }
        return lcp;
    }

    public static void main(String[] args) {
        String str = "banana";
        SaNode rankArr = getRankArr(str);
        System.out.println(rankArr);
        System.out.println(Arrays.toString(getLCP(rankArr, str)));
    }
}
