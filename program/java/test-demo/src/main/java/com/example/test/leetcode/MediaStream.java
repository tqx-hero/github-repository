package com.example.test.leetcode;

import com.example.test.heap.BigHeap;
import com.example.test.heap.SmallHeap;

import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个持续加载的数据流
 * @date 2026/3/1 9:48
 */
public class MediaStream {

//    public int size = 0;

    //大顶堆存放较小数据
    public BigHeap left;
    //小顶堆存放较大数据
    public SmallHeap right;

    @Override
    public String toString() {
        return "MediaStream{" +
                "left=" + left +
//                ", size=" + size +
                ", right=" + right +
                '}';
    }

    /**
     * 数据入大顶堆
     *
     * @param i
     */
    void pushLeft(int i) {
        left.add(i);
//        size++;
    }

    /**
     * 数据入小顶堆
     *
     * @param i
     */
    void pushRight(int i) {
        right.add(i);
//        size++;
    }

    void init(int i) {
        if (Objects.isNull(left)) {
            left = new BigHeap();
            left.add(i);
            return;
        }
        if (Objects.isNull(right)) {
            right = new SmallHeap();
        }
        //传入数据大于大顶堆堆顶数据，则再次比较与小顶堆堆顶,大于堆顶则直接入堆，小于等于则还是入大顶堆，完事平衡两堆的数据
        if (right.size == 0) {
            if (left.getTop() <= i) right.add(i);
            else {
                right.add(left.getTop());
                left.del();
                left.add(i);
            }
            return;
        }
        //大顶堆的堆顶数据比传入数据大，则入堆,同时比较与小顶堆数据量，进行平衡
        //num(大顶堆) - num(小顶堆) >1个，大顶堆堆顶删除，入小顶堆
        if (i > right.getTop())
            right.add(i);
        else
            left.add(i);

        if (right.size > left.size) {
            left.add(right.getTop());
            right.del();
        }
        if (left.size - right.size > 1) {
            right.add(left.getTop());
            left.del();
        }
    }

    /**
     * 加载空数据流
     */
    public void init() {
        left = new BigHeap();
        right = new SmallHeap();
    }

}
