package org.example.cond;

import java.util.ArrayDeque;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: 加入条件队列实现生产者消费者
 * @date 2026/5/19 14:52
 */
public class ProducerAndConsumer {

    private static final int MAX_SIZE = 1 << 6;
    private static final ReentrantLock LOCK = new ReentrantLock();
    private static final Condition EMPTY = LOCK.newCondition();
    private static final Condition FULL = LOCK.newCondition();
    private static final ArrayDeque<Integer> QUEUE = new ArrayDeque<>(MAX_SIZE);
    private static volatile int num = 0;

    private static final class Producer extends Thread {

        @Override
        public void run() {
            while (true) {
                try {
                    LOCK.lock();
                    while (QUEUE.size() == MAX_SIZE)
                        FULL.await();
                    System.out.println("生产者生产了数据：" + num);
                    QUEUE.offer(num++);
                    EMPTY.signal();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                } finally {
                    LOCK.unlock();
                }
                try {
                    sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    private static final class Consumer extends Thread {

        @Override
        public void run() {
            while (true) {
                try {
                    LOCK.lock();
                    while (QUEUE.isEmpty())
                        EMPTY.await();
                    System.out.println("消费者消费了数据：" + QUEUE.poll());
                    FULL.signal();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                } finally {
                    LOCK.unlock();
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
