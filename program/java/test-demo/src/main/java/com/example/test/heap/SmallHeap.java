package com.example.test.heap;

import java.util.Arrays;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个小顶堆
 * @date 2026/3/1 9:46
 */
public class SmallHeap {

    public int parIdx = -1;
    private static final int MAX_SIZE = 10;
    private int[] hepArray;

    @Override
    public String toString() {
        return "SmallHeap{" +
                "hepArray=" + Arrays.toString(hepArray) +
                ", parIdx=" + parIdx +
                ", size=" + size +
                '}';
    }

    public SmallHeap(int[] hepArray) {
        this.hepArray = hepArray;
    }

    public SmallHeap() {
    }

    public int size = 0;


    /**
     * 给堆添加数据，小堆实现上浮
     *
     * @param v
     */
    public void add(int v) {
        if (Objects.isNull(hepArray))
            hepArray = new int[MAX_SIZE];
        hepArray[size++] = v;
        //小堆比较最新数据与父节点，比父节点小则上浮,以此类推
        if (size > 1) {
//            parIdx = (size - 1) >> 1;
            swim(size - 1, v);
        }

    }

    private void swim(int parIdx, int val) {
        int parentIdx = parIdx - 1 < 0 ? parIdx - 1 : (parIdx - 1) >> 1;
        if (parentIdx < 0) {
            return;
        }
        int par = hepArray[parentIdx];
        if (par > val) {
            hepArray[parentIdx] = val;
            hepArray[parIdx] = par;
            swim(parentIdx, val);
        }

    }

    /**
     * 删除小顶堆的堆顶
     */
    public void del() {
//        if (size == 0) return;
        if (size < 1) hepArray[0] = 0;
        else {
            //将最末端数值赋给根节点，同时进行下沉操作
            hepArray[0] = hepArray[size - 1];
            hepArray[(size--) - 1] = 0;

            //根节点与子节点数值比较，大就下沉
            sink(0);
        }
    }

    /**
     * 小顶堆删除头后下沉数据
     *
     * @param parIdx 删除的索引
     */
    void sink(int parIdx) {
        if (parIdx >= size) {
            return;
        }
        int leftIdx = (parIdx << 1) + 1;
        int rightIdx = (parIdx + 1) << 1;
        int childInx = 0;
        if (leftIdx >= size) return;
        if (rightIdx < size && hepArray[rightIdx] < hepArray[leftIdx] && hepArray[rightIdx] < hepArray[parIdx]) {
            childInx = rightIdx;
        } else if (hepArray[leftIdx] < hepArray[parIdx]) {
            childInx = leftIdx;
        }
        if (childInx != 0) {
            int tmp = hepArray[childInx];
            hepArray[childInx] = hepArray[parIdx];
            hepArray[parIdx] = tmp;
            sink(childInx);
        }
    }

    /**
     * 获取堆顶数据
     *
     * @return
     */
    public int getTop() {
        return size == 0 ? 0 : hepArray[0];
    }

}
