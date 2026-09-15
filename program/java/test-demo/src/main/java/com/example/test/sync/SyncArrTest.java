package com.example.test.sync;


import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.stream.Collectors;

/**
 * @author Administrator
 * @version 1.0
 * @description: synchronized 锁定final定义的数组中某个元素，使其锁的粒度更细，增加并发时访问速度
 * @date 2026/2/24 7:35
 */
public class SyncArrTest {

    private int[] count = new int[10];
    private final Object[] lock = {new Object(), new Object()};


    void add(int index, int value) {
        if (index <= count.length / 2) {
            synchronized (lock[0]) {
                count[index] = value;
                System.out.println(Thread.currentThread().getName() + " count[" + index + "] = " + value);
            }
        } else {
            synchronized (lock[1]) {
                count[index] = value;
                System.out.println(Thread.currentThread().getName() + " count[" + index + "] = " + value);
            }
        }
//        System.out.println(Thread.currentThread().getName() + " :执行非同步逻辑");
    }

    public static void main(String[] args) {
        int[] arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        List<Integer> integers = new ArrayList<>();
        Arrays.stream(arr).mapToObj((a) -> {
            integers.add(a * 100);
            return integers;
        }).collect(Collectors.toList());
        SyncArrTest syncArrTest = new SyncArrTest();
        new Thread(() -> {
            for (int i = 0; i < integers.size(); i++) {
                syncArrTest.add(i, integers.get(i));
            }
        }, "线程1").start();
    }

}
