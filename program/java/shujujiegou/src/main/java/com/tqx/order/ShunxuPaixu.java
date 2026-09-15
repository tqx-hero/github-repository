package com.tqx.order;

/**
 * @author Administrator
 * @version 1.0
 * @description: 直接排序
 * 添加哨兵节点用来存放要排序的数据，从后往前依次与哨兵节点数据对比，小的调换位置
 * @date 2026/4/5 20:24
 */
public class ShunxuPaixu {

    //直接插入法，从后往前找，直到前面的数不大于要插入的数
    public static int[] order(int[] arr) {
        if (arr == null || arr.length == 0)
            return new int[]{};
        int length = arr.length;
        //设置一个新的数组，长度+1，头结点作为哨兵节点可用来存放数据
        int[] orderArr = new int[length + 1];
        int sentinelIndex = 0;
        for (int i = 0; i < length; i++) {
            orderArr[sentinelIndex] = arr[i];
            for (int j = i + 1; ; j--) {
                //从后往前遍历数组中的所有数据直到大于它
                if (orderArr[j - 1] > orderArr[sentinelIndex]) {
                    orderArr[j] = orderArr[j - 1];
                    continue;
                }
                orderArr[j] = orderArr[sentinelIndex];
                break;
            }
        }
        return orderArr;
    }

    //折半查找
    public static int[] halfSearch(int[] arr) {
        if (arr == null || arr.length == 0)
            return new int[]{};
        int[] arrs = new int[arr.length + 1];
        int sentinel = 0;
        arrs[sentinel + 1] = arr[sentinel];
        for (int i = 1; i < arr.length; i++) {
            arrs[sentinel] = arr[i];
            int head = 1, tail = i;
            if (arrs[tail] < arrs[sentinel]) {
                arrs[tail + 1] = arrs[sentinel];
                continue;
            }
            for (; head <= tail; ) {
                if (head == tail) {
                    if (arrs[tail] < arrs[sentinel])
                        tail++;
                    break;
                }
                //head 小，tail大，而且head与tail相距不超过1
                int mid = (head + tail) >>> 1;
                //mid小于，tail前移
                if (arrs[mid] < arrs[sentinel])
                    head = mid + 1;
                else
                    tail = mid - 1;
            }
            for (int j = i; j >= tail; j--)
                arrs[j + 1] = arrs[j];
            arrs[tail] = arrs[sentinel];
        }
        return arrs;
    }

    public static void main(String[] args) {
        int[] arr = {22, 10, 30, 20, 80, 7, 50, 33};
//        int[] arrs = ShunxuPaixu.order(arr);

        int[] arrs = ShunxuPaixu.halfSearch(arr);
        for (int i = 1; i < arrs.length; i++) {
            System.out.println(arrs[i]);
        }
    }
}
