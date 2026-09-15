package com.tqx.order;

import java.util.Arrays;
import java.util.PriorityQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 创建一个小根堆
 * @date 2026/4/7 8:59
 */
public class MinHeap {
    private static final int DEFAULT_CAPACITY = 1 << 6;
    private Integer[] val;
    private int count;

    public MinHeap() {
        this.val = new Integer[DEFAULT_CAPACITY];
        count = 0;
    }

    public void add(Integer v) {
        //添加到数组，开始上浮
        int cur, p;
        for (cur = count; cur > 0 && v.compareTo(val[p = ((cur - 1) >>> 1)]) < 0; cur = p)
            val[cur] = val[p];
        val[cur] = v;
        count++;
    }

    public int peek() {
        return val[0];
    }

    public int poll() {
        //把最后一个元素添加到堆顶位置，然后下沉
        int res = val[0];
        int temp = val[count - 1];
        count--;
        int cur, c1;
        for (cur = 0; (c1 = cur * 2 + 1) <= count - 1; cur = c1) {
            //这里判断另一个儿子是否存在以及数据是否小于c1
            //小于的话c1+1即可
            if (c1 != count - 1 && val[c1 + 1] < val[c1])
                c1++;
            if (temp <= val[c1])
                break;
            val[cur] = val[c1];
        }
        val[cur] = temp;
        return res;
    }

    public Integer[] getHeap() {
        return Arrays.copyOfRange(val, 0, count);
    }

    public static void main(String[] args) {
        MinHeap minHeap = new MinHeap();
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
        for (int i : arr) {
            minHeap.add(i);
        }
        System.out.println(minHeap.poll());
        System.out.println(minHeap.poll());
        System.out.println(Arrays.toString(minHeap.getHeap()));
    }
}
