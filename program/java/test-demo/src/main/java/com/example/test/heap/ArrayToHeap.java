package com.example.test.heap;

import com.example.test.util.ObjectUtils;

import javax.validation.constraints.Size;
import java.util.Arrays;

import static com.example.test.heap.HeapVO.MAX_SIZE;

/**
 * @author Administrator
 * @version 1.0
 * @description: 将一个无序数组生成一个大顶堆:批量下沉
 * @date 2026/2/28 16:16
 */
public class ArrayToHeap {


    public HeapVO initBigHeap(int[] arr) {
        HeapVO heapVO = new HeapVO(Arrays.copyOf(arr, MAX_SIZE), arr.length);
        if (heapVO.size == 0) return null;
        if (heapVO.size == 1) return heapVO;
        int parIdx = (heapVO.size - 1 - 1) >> 1;

        for (int i = parIdx; i >= 0; i--) {
            heapVO = batchSink(i, heapVO);
        }

        return heapVO;
    }

    /**
     * 批量下沉
     *
     * @param index
     * @param heapVO
     * @return
     */
    public HeapVO batchSink(int index, HeapVO heapVO) {
        int[] arr = heapVO.hepArray;
        if (index < 0) {
            return heapVO;
        }
        //获取该节点的子节点
        int left = (index << 1) + 1;
        int right = (index + 1) << 1;
        if (left >= heapVO.size) return heapVO;
        int child = -1;
        if (right < heapVO.size && arr[right] > arr[left] && arr[right] > arr[index]) {
            child = right;
        } else if (arr[left] > arr[index]) {
            child = left;
        }
        if (child != -1) {
            int tmp = arr[child];
            arr[child] = arr[index];
            arr[index] = tmp;
            heapVO = batchSink(child, heapVO);
        }
        return heapVO;
//        return batchSink(child, heapVO);
    }

    /**
     * 拿出大顶堆的最大值
     *
     * @param heapVO
     * @return
     */
    public int getBiggest(HeapVO heapVO) {
        int res = -1;
        if (heapVO.size == 0) return res;
        if (heapVO.size == 1) {
            res = heapVO.hepArray[0];
            heapVO.hepArray[0] = 0;
            heapVO.size = 0;
            heapVO.parIdx = -1;
            return res;
        }
        //将大顶堆的根节点与最末尾子节点对调
        ObjectUtils.swap(heapVO.hepArray, 0, heapVO.size - 1);
        res = heapVO.hepArray[(heapVO.size) - 1];
        heapVO.hepArray[(heapVO.size--) - 1] = 0;
        //从根节点开始依次重置堆结构
        batchSink(0, heapVO);
        return res;
    }

    /**
     * 大顶堆顺序放到数组里面
     *
     * @param heapVO
     * @return
     */
    public HeapVO orderAsc(HeapVO heapVO) {
        int iter = heapVO.size;
        while (heapVO.size > 0) {
            //1、先把堆顶与最末节点数据互换
            ObjectUtils.swap(heapVO.hepArray, 0, (heapVO.size--) - 1);
            //2、对堆进行下沉排序
            batchSink(0, heapVO);
        }
        heapVO.size = iter;
        //3、重复1、2 步骤，直到将堆内数据取完
        return heapVO;
    }


    public static void main(String[] args) {
        ArrayToHeap arrayToHeap = new ArrayToHeap();
        HeapVO heapVO = arrayToHeap.initBigHeap(new int[]{20, 3, 5, 100, 88, 22, 30, 33, 21});
        System.out.println(heapVO);
        heapVO = arrayToHeap.orderAsc(heapVO);
        System.out.println(heapVO);
//        int i = arrayToHeap.getBiggest(heapVO);
//        HeapVO heapVO = arrayToHeap.initBigHeap(new int[]{20, 3, 5, 100});
    }
}
