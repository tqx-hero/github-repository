package com.tqx.find;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 分块查找
 * @date 2026/4/3 10:40
 */
public class FenkuaiSearch {

    //所有数据存放位置
    private int[] obj;
    private int objNum;
    //分块区间，一块区域有多少数据
    private int keySize;
    //数据分块的key，存放这一块的数据最大值，数组所在的起始位置
    private KeyEntry[] keyArr;

    @Override
    public String toString() {
        return "FenkuaiSearch{" +
                "keyArr=" + Arrays.toString(keyArr) +
                ", obj=" + Arrays.toString(obj) +
                ", objNum=" + objNum +
                ", keySize=" + keySize +
                '}';
    }

    static class KeyEntry {
        //该块区域的最大值
        int maxVal;
        //在obj数据数组中的始末index
        int beginIndex;
        int endIndex;

        @Override
        public String toString() {
            return "KeyEntry{" +
                    "beginIndex=" + beginIndex +
                    ", maxVal=" + maxVal +
                    ", endIndex=" + endIndex +
                    '}';
        }

        public KeyEntry(int beginIndex, int endIndex) {
            this.beginIndex = beginIndex;
            this.endIndex = endIndex;
        }
    }

    public FenkuaiSearch(int[] obj) {
        this.obj = obj;
        objNum = obj.length;
    }

//int[] obj = {3, 55, 22, 44,  77, 88, 66,58,  89,99,100,2333};

    private void init(int num) {
        if (num <= 0)
            throw new IllegalArgumentException("分块中数据的数量不能为0");
        //分块
        this.keySize = num;
        int i1 = objNum / keySize;
        int keyArrLength = objNum % keySize == 0 ? i1 : i1 + 1;
        keyArr = new KeyEntry[keyArrLength];
        //查找每一块的最大值
        for (int k = 0; k < keyArrLength; k++) {
            int begin = k * keySize;
            int end = Math.min((k + 1) * keySize - 1, objNum - 1);
            keyArr[k] = new KeyEntry(begin, end);
            int maxNum = obj[begin];
            for (; begin <= end; begin++) {
                int max = obj[begin];
                if (max > maxNum)
                    maxNum = max;
            }
            keyArr[k].maxVal = maxNum;
        }
    }

//    public void init(int num) {
//        //分块计算
//        //每一块的最大值，起始index
//        createKey(4);
//
//    }

    public int findNumIndex(int num) {
        //拿到索引
        int beginIndex = -1;
        int endIndex = -1;
        for (KeyEntry entry : keyArr) {
            if (num <= entry.maxVal) {
                beginIndex = entry.beginIndex;
                endIndex = entry.endIndex;
                break;
            }
        }
        if (beginIndex < 0)
            return -1;
        for (; beginIndex <= endIndex; beginIndex++) {
            if (obj[beginIndex] == num)
                return beginIndex;

        }
        return -1;
    }

    public static void main(String[] args) {
        int[] obj = {3, 55, 22, 44, 77, 88, 66, 58, 89, 99, 100, 2333};
        FenkuaiSearch fo = new FenkuaiSearch(obj);
        fo.init(4);
        System.out.println(fo.findNumIndex(55));
    }

}
