package com.tqx.sort;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: 堆排序
 * @date 2026/4/16 10:29
 */
public class HeapSort {

    private int[] arr;
    private int size;
    private int count;

    public HeapSort(int[] arr) {
        this.size = arr.length;
        count = size;
        this.arr = Arrays.copyOf(arr, size);
        initHeap();
    }

    private void initHeap() {
        //下沉起始位置
        for (int i = size / 2 - 1; i >= 0; i--)
            sink(i, size);
    }

    private void sink(int k, int size) {
        int j = 2 * k + 1;
        for (; j < size; j = 2 * k + 1) {
            int m = j;
            //判断有无右孩子
            if (j < size - 1 && arr[j + 1] < arr[j]) {
                m = j + 1;
            }
            if (arr[k] <= arr[m])
                break;
            //小于则交换
            int tmp = arr[k];
            arr[k] = arr[m];
            arr[m] = tmp;
            k = m;
        }
    }

    public boolean isEmpty() {
        return count == 0;
    }

    public int deleteMin() {
        if (count == 0)
            throw new NullPointerException("堆已为空");
        int m = arr[0];
        arr[0] = arr[count - 1];
        sink(0, count - 1);
        arr[(count--) - 1] = 0;
        return m;
    }

    @Override
    public String toString() {
        return "HeapSort{" +
                "arr=" + Arrays.toString(arr) +
                ", size=" + size +
                ", count=" + count +
                '}';
    }

    public HeapSort(int size) {
        this.size = size;
        this.arr = new int[size];
        count = 0;
    }

    public static int[] sort(int[] a) {
        if (a == null || a.length <= 1)
            return a;
        HeapSort sort = new HeapSort(a);
        int index = 0;
        while (!sort.isEmpty())
            a[index++] = sort.deleteMin();
        return a;
    }

    public static void main(String[] args) {
        int[] arr = {142, 543, 123, 65, 453, 879, 572, 434, 111, 242, 811, 102};
        System.out.println(Arrays.toString(sort(arr)));
    }
}
