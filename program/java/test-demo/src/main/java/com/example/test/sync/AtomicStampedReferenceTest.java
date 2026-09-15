package com.example.test.sync;

import java.util.concurrent.atomic.AtomicStampedReference;

/**
 * @author Administrator
 * @version 1.0
 * @description: AtomicStampReference解决AtomicInteger等原子类CAS出现ABA问题，通过增加版本号
 * @date 2026/2/24 9:15
 */
public class AtomicStampedReferenceTest {

    private static final AtomicStampedReference<Integer> stampedReference = new AtomicStampedReference<>(1, 0);
    private static int stamp;

    static {
        stamp = stampedReference.getStamp();
    }

    public static void main(String[] args) throws InterruptedException {

        Thread thread1 = new Thread(() -> {
            stampedReference.compareAndSet(1, 2, stampedReference.getStamp(), stampedReference.getStamp() + 1);
            System.out.println("1====" + stampedReference.getReference() + ",v===" + stampedReference.getStamp());

            stampedReference.compareAndSet(2, 1, stampedReference.getStamp(), stampedReference.getStamp() + 1);
            System.out.println("2====" + stampedReference.getReference() + ",v===" + stampedReference.getStamp());
        }, "线程1制造ABA问题");

        Thread thread2 = new Thread(() -> {
            boolean boo =
                    stampedReference.compareAndSet
                            (stampedReference.getReference(), 3, stamp, stampedReference.getStamp() + 1);
            System.out.println("线程2是否执行成功？:" + boo);
            System.out.println("线程2结果？:" + stampedReference.getReference() + ",版本号=" + stampedReference.getStamp());
        }
                , "线程2");

        thread1.start();
        thread1.join();
        thread2.start();
        thread2.join();
//        System.out.println("结果== " + stampedReference.getReference() + ",版本号：" + stampedReference.getStamp());
    }
}
