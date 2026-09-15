package com.example.test.heap;

import java.util.Arrays;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/28 13:32
 */
public class HeapDemo {

    public int parIdx = -1;
    private static final int MAX_SIZE = 100;
    private int[] hepArray;
//    public HeapDemo() {
//    }

    @Override
    public String toString() {
        return "HeapDemo{" +
                "hepArray=" + Arrays.toString(hepArray) +
                '}';
    }

//    public HeapDemo(int[] hepArray) {
//        this.hepArray = Arrays.copyOf(hepArray, MAX_SIZE);
//    }

    private int size = 0;

    public HeapDemo() {
    }

    /**
     * 给堆添加数据，大堆实现上浮
     *
     * @param v
     */
    public void add(int v) {
        if (Objects.isNull(hepArray))
            hepArray = new int[MAX_SIZE];
        hepArray[size++] = v;
        //大堆比较最新数据与父节点，比父节点大则上浮,以此类推
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
        if (par < val) {
            hepArray[parentIdx] = val;
            hepArray[parIdx] = par;
            swim(parentIdx, val);
        }

    }

    /**
     * 删除大顶堆的堆顶
     */
    void del() {
//        if (size == 0) return;
        if (size <= 1) hepArray[0] = 0;
        else {
            //将最末端数值赋给根节点，同时进行下沉操作
            hepArray[0] = hepArray[size - 1];
            hepArray[(size--) - 1] = 0;

            //根节点与子节点数值比较，小就下沉
            sink(0);
        }
    }

    /**
     * 大顶堆删除头后下沉数据
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
        if (rightIdx < size && hepArray[rightIdx] > hepArray[leftIdx] && hepArray[rightIdx] > hepArray[parIdx]) {
            childInx = rightIdx;
        } else if (hepArray[leftIdx] > hepArray[parIdx]) {
            childInx = leftIdx;
        }
        if (childInx != 0) {
            int tmp = hepArray[childInx];
            hepArray[childInx] = hepArray[parIdx];
            hepArray[parIdx] = tmp;
            sink(childInx);
        }

    }

    public static void main(String[] args) {
        HeapDemo demo = new HeapDemo();
        demo.add(20);
        demo.add(30);
        demo.add(40);
        demo.add(60);
        demo.add(90);
        demo.add(62);
        demo.add(88);
        System.out.println(demo);

        demo.del();
        demo.del();
        System.out.println(demo);

    }

}
