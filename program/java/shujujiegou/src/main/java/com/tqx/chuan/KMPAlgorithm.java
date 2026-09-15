package com.tqx.chuan;

/**
 * @author Administrator
 * @version 1.0
 * @description: KMP算法
 * @date 2026/4/13 9:52
 */
public class KMPAlgorithm {

    //暴力算法求最长前后缀相等的最大长度
    public static int[] getNext(String s) {
        if (s == null || s.isEmpty())
            return new int[]{};
        char[] sArr = s.toCharArray();
        int length = sArr.length;
        var next = new int[length];
        //直接跳过第一第二位
        //他俩没有前后缀或只有其中一个
        for (int i = 2; i < length; i++) {
            //前后缀的最大长度
            int max = i / 2;
            for (var k = max; k > 0; k--) {
                boolean equals = false;
                for (int j = 0; j < k; j++) {
                    if (sArr[j] == sArr[i - k + j]) {
                        equals = true;
                        continue;
                    }
                    equals = false;
                    break;
                }
                if (equals) {
                    next[i] = k;
                    break;
                }
            }
        }
        return next;
    }

    //KMP算法的计算next[]方式
    public static int[] next(String s) {
        char[] a = s.toCharArray();
        int l = a.length;
        var next = new int[l];
        int j;
        for (int i = 2; i < l; i++) {
            //先获取到前一个元素的next值
//            //不相同需要查看下next[i-1]是否为0，往前递推直到0为止
            for (j = next[i - 1]; j > 0 && a[i - 1] != a[j]; j = next[j]) ;
            next[i] = a[i - 1] == a[j] ? j + 1 : 0;
        }
        return next;
    }

    public static int getIndex(String str, String s) {
        if (str == null || s == null || str.isEmpty() || s.isEmpty() || s.length() > str.length())
            return -1;
        char[] a = s.toCharArray(), b = str.toCharArray();
        int n = a.length, m = b.length;
        int[] next = next(s);
        int i = 0, j = 0;
        while (i < m && j < n) {
            if (b[i] == a[j]) {
                i++;
                j++;
            } else
                //字符不匹配，j回退到next[j],i不回退
                if (j == 0)
                    i++;
                else
                    j = next[j];
        }
        return j < n ? -1 : i - n;
    }

    public static void main(String[] args) {
        String str = "TTTTCACTCAC";
        String s = "CACTCAC";
        System.out.println(getIndex(str, s));
//        System.out.println(Arrays.toString(next(s)));
    }
}
