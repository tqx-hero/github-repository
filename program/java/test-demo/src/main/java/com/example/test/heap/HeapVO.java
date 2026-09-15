package com.example.test.heap;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 声明一个大顶堆
 * @date 2026/2/28 16:16
 */
public class HeapVO {
    public int parIdx = -1;
    public static final int MAX_SIZE = 30;
    public int[] hepArray;
    public int size = 0;

    public HeapVO(int[] hepArray) {
        this.hepArray = hepArray;
    }

    @Override
    public String toString() {
        return "HeapVO{" +
                "hepArray=" + Arrays.toString(hepArray) +
                ", parIdx=" + parIdx +
                ", size=" + size +
                '}';
    }

    public HeapVO(int[] hepArray, int size) {
        this.hepArray = hepArray;
        this.size = size;
    }

    public HeapVO() {
    }
}
