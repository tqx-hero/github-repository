package org.example.sem;

import java.util.ArrayDeque;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

/**
 * @author Administrator
 * @version 1.0
 * @description: semaphore解决生产者与消费者之间的矛盾
 * @date 2026/5/18 10:58
 */
public class ProducerAndConsumer {
    //设置锁，许可设置为1
    private static final Semaphore LOCK = new Semaphore(1);
    //设置初始值空位置数量与满位置数量
    private static final Semaphore EMPTY = new Semaphore(100);
    private static final Semaphore FULL = new Semaphore(0);
    private static final ArrayDeque<Integer> QUEUE = new ArrayDeque<>();
    private static volatile int product = 1;

    public static class Producer extends Thread {
        public void run() {
            while (true) {
                //先设置空槽数量
                try {
                    EMPTY.acquire();
                    LOCK.acquire();
                    QUEUE.offer(product++);
                    LOCK.release();
                    FULL.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }


    public static class Consumer extends Thread {
        public void run() {
            while (true) {
                try {
                    FULL.acquire();
                    LOCK.acquire();
                    System.out.println("取出数据:" + QUEUE.poll());
                    LOCK.release();
                    EMPTY.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }


    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            new Producer().start();
        }
        for (int i = 0; i < 10; i++) {
            new Consumer().start();
        }
    }

}
