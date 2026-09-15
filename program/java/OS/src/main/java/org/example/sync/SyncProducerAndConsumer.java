package org.example.sync;

import java.util.ArrayDeque;

/**
 * @author Administrator
 * @version 1.0
 * @description: synchronized解决生产者消费者问题
 * @date 2026/5/19 14:31
 */
public class SyncProducerAndConsumer {

    private static volatile int num = 0;
    private static final ArrayDeque<Integer> QUEUE = new ArrayDeque<>(64);

    private static class Producer extends Thread {

        @Override
        public void run() {
            while (true) {
                synchronized (QUEUE) {
                    while (QUEUE.size() == 64) {
                        try {
                            QUEUE.wait();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    System.out.println("生产了数据:" + num);
                    QUEUE.offer(num++);
                    //如果生产数据之前队列为空，唤醒等待的消费者
                    QUEUE.notifyAll();
                }
                try {
                    sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    private static class Consumer extends Thread {
        @Override
        public void run() {
            while (true) {
                synchronized (QUEUE) {
                    while (QUEUE.isEmpty()) {
                        try {
                            QUEUE.wait();
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    System.out.println("消费了数据：" + QUEUE.poll());
                    QUEUE.notifyAll();
                }
                try {
                    sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            new Producer().start();
            new Consumer().start();
        }
    }

}
