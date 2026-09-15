package org.example.jvm.test;

/**
 * Java 死锁测试用例
 * 场景：两个线程分别尝试获取对方已持有的锁，形成循环等待，最终死锁
 */
public class DeadLockTest {
    // 定义两个作为锁的对象（核心：两个独立的锁资源）
    private static final Object LOCK_A = new Object();
    private static final Object LOCK_B = new Object();

    public static void main(String[] args) {
        // 线程1：先获取LOCK_A，再尝试获取LOCK_B
        Thread thread1 = new Thread(() -> {
            synchronized (LOCK_A) {
                System.out.println(Thread.currentThread().getName() + " 已获取锁 LOCK_A，等待获取 LOCK_B");
                try {
                    // 休眠1秒，确保线程2先获取LOCK_B，放大死锁概率
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                // 尝试获取LOCK_B（此时LOCK_B已被线程2持有）
                synchronized (LOCK_B) {
                    System.out.println(Thread.currentThread().getName() + " 成功获取锁 LOCK_B");
                }
            }
        }, "Thread-1");

        // 线程2：先获取LOCK_B，再尝试获取LOCK_A
        Thread thread2 = new Thread(() -> {
            synchronized (LOCK_B) {
                System.out.println(Thread.currentThread().getName() + " 已获取锁 LOCK_B，等待获取 LOCK_A");
                try {
                    // 休眠1秒，确保线程1先获取LOCK_A
                    Thread.sleep(1000);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                // 尝试获取LOCK_A（此时LOCK_A已被线程1持有）
                synchronized (LOCK_A) {
                    System.out.println(Thread.currentThread().getName() + " 成功获取锁 LOCK_A");
                }
            }
        }, "Thread-2");

        // 启动两个线程
        thread1.start();
        thread2.start();
    }
}
