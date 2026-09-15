package com.tqx.thread.condition;

import java.util.ArrayDeque;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: 简易版阻塞队列
 * @date 2026/3/19 8:19
 */
public class SimpleBlockQueue<T> extends ArrayDeque<T> {

    private ReentrantLock lock = new ReentrantLock();
    private Condition full = lock.newCondition();
    private Condition empty = lock.newCondition();

    private int size;

    private SimpleBlockQueue() {
    }

    public SimpleBlockQueue(int numElements) {
        super(numElements);
        this.size = numElements;
    }

    public boolean put(T obj) {
        //入队，判断队列是否满，满则需要阻塞在这里
        try {
            lock.lock();
            while (size == size())
                full.await();
            boolean b = add(obj);
            empty.signal();
            return b;
        } catch (Exception e) {
        } finally {
            if (lock.isHeldByCurrentThread()) {
                lock.unlock();
            }
        }
        return false;
    }

    public T take() {
        try {
            lock.lock();
            while (isEmpty())
                empty.await();
            T t = poll();
            full.signal();
            return t;
        } catch (Exception e) {
        } finally {
            if (lock.isHeldByCurrentThread()) {
                lock.unlock();
            }
        }
        return null;
    }

}

class Test {
    public static void main(String[] args) {
        SimpleBlockQueue<Integer> blockQueue = new SimpleBlockQueue<>(10);
        for (int i = 0; i < 10; i++) {
            final int finalI = i;
            new Thread(() -> {
                try {
                    TimeUnit.MILLISECONDS.sleep(200);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
                blockQueue.put(finalI);
            }).start();
        }

        for (int i = 0; i < 10; i++) {
            final int finalI = i;
            new Thread(() -> {
                try {
                    TimeUnit.SECONDS.sleep(1);
                    blockQueue.take();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
//                System.out.println("num= " + blockQueue.take());
            }).start();
        }


    }
}
