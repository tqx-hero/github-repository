package com.tqx.thread.message;

import java.util.concurrent.ArrayBlockingQueue;

/**
 * @author Administrator
 * @version 1.0
 * @description: 简单实现消息队列功能
 * @date 2026/3/15 21:10
 */
public class MessageQueue {

    private static Integer queueSize;
    private static ArrayBlockingQueue<Integer> queue;

    static {
        queueSize = 20;
        queue = new ArrayBlockingQueue<>(queueSize);
    }


    public static void main(String[] args) {
        new Consumer().start();
        for (int i = 0; i < 40; i++) {
            new Producer().start();
        }
    }

    static class Producer extends Thread {
        @Override
        public void run() {
            synchronized (queue) {
                //判断队列是否已满，已满则等待
                if (queue.size() >= queueSize) {
                    try {
                        queue.wait();
                    } catch (InterruptedException e) {
                        queue.notify();
                    }
                } else {
                    queue.add(queue.size() + 1);
                    System.out.println("生产者: [" + Thread.currentThread().getName() + "] 生产了消息: " + queue.size());
                    queue.notify();
                }
            }
        }
    }

    static class Consumer extends Thread {
        @Override
        public void run() {

            while (true) {
                //先拿到锁
                synchronized (queue) {
                    //判断队列是否为空，为空则等待生产者生产消息
                    if (queue.isEmpty()) {
                        try {
                            queue.wait();
                        } catch (InterruptedException e) {
                            //中断异常以后线程仍然在等待队列中，必须注意唤醒
                            queue.notify();
                        }
                    } else {
                        //队列不为空，就开始消费
                        Integer message = queue.poll();
                        System.out.println("消费者 [" + Thread.currentThread().getName() + "] 消费了消息： " + message + ", 当前队列长度为： " + queue.size());
                        queue.notify();
                    }
                }
            }
        }
    }
}
