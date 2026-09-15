package com.tqx.thread.sync;

import org.openjdk.jol.info.ClassLayout;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/16 8:29
 */
public class SyncTest {

    private Integer num;

    public static void main(String[] args) throws InterruptedException {
        SyncTest syncTest = new SyncTest();
        synchronized (syncTest) {
            System.out.println(ClassLayout.parseInstance(syncTest).toPrintable());

        }
        Thread.sleep(5000);
        System.out.println(ClassLayout.parseInstance(syncTest).toPrintable());
        Thread thread = new Thread(() -> {
            synchronized (syncTest) {
                System.out.println(ClassLayout.parseInstance(syncTest).toPrintable());
            }
        });
//        Thread thread1 = new Thread(() -> {
//            synchronized (syncTest) {
//                System.out.println(ClassLayout.parseInstance(syncTest).toPrintable());
//            }
//        });
        thread.start();
//        thread1.start();
        thread.join();
//        thread1.join();
        System.out.println(ClassLayout.parseInstance(syncTest).toPrintable());
    }

}
