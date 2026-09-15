package org.example.sem;

import java.util.concurrent.Semaphore;

/**
 * @author Administrator
 * @version 1.0
 * @description: 读者与写者的问题
 * 1、读者之间不互斥
 * 2、写者与写者互斥
 * 3、写者与读者互斥
 * @date 2026/5/18 20:31
 */
public class ReaderAndWriter {
    //设置写锁，实现读写互斥
    private static final Semaphore WRITE = new Semaphore(1);
    //第一个读者标记，用来让第一个读者进行加写锁，后续读者不需要再加写锁
    private static int count = 0;
    //保证count操作的原子性，给它加锁
    private static final Semaphore MUTEX = new Semaphore(1);
    //由于读者在count=0时才会解写锁，并且读操作共享
    //为了使写不会线程饥饿，增加一个互斥量，用来控制读写顺序，使读操作可以有机会排在写
    //后面
    private static final Semaphore LOCK = new Semaphore(1);

    private static class Writer extends Thread {
        @Override
        public void run() {
            while (true) {
                try {
                    LOCK.acquire();
                    WRITE.acquire();
                    System.out.println("写者正在写入文件");
                    WRITE.release();
                    LOCK.release();
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    private static class Reader extends Thread {
        @Override
        public void run() {
            while (true) {
                try {
                    LOCK.acquire();
                    MUTEX.acquire();
                    if (count++ == 0)
                        WRITE.acquire();
                    MUTEX.release();
                    LOCK.release();
                    System.out.println("读者正在读文件");
                    MUTEX.acquire();
                    if (--count == 0)
                        WRITE.release();
                    MUTEX.release();
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) {
        for (int i = 0; i < 10; i++) {
            new Writer().start();
            new Reader().start();
        }
    }

}
