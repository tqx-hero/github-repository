package com.spring.singleton;

import org.springframework.stereotype.Component;

import java.util.concurrent.atomic.AtomicStampedReference;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 9:52
 */
@Component
public class Salary {

            public static volatile int salary = 1000;
//    public static volatile AtomicStampedReference<Integer> salary = new AtomicStampedReference<>(1000, 0);
//    public void add(int num) {
//        boolean isSuccess = true;
//        do {
//            int oldStamp = salary.getStamp();
//            Integer oldReference = salary.getReference();
//            if (oldStamp == salary.getStamp() && oldReference.equals(salary.getReference())) {
//                int i = oldReference + num;
//                try {
//                    Thread.sleep(3000);
//                } catch (InterruptedException e) {
//                    throw new RuntimeException(e);
//                }
//                isSuccess = salary.weakCompareAndSet(oldReference, i, oldStamp, ++oldStamp);
//            }
//        } while (!isSuccess);
//    }
//
//    public void mit(int num) {
//        boolean isSuccess = true;
//        do {
//            int oldStamp = salary.getStamp();
//            Integer oldReference = salary.getReference();
//            if (oldStamp == salary.getStamp() && oldReference.equals(salary.getReference())) {
//                int i = oldReference - num;
//                try {
//                    Thread.sleep(1000);
//                } catch (InterruptedException e) {
//                    throw new RuntimeException(e);
//                }
//                isSuccess = salary.weakCompareAndSet(oldReference, i, oldStamp, ++oldStamp);
//            }
//        } while (!isSuccess);
//    }
    public void add(int num) {
        synchronized (this) {
            int i = salary + num;
            try {
                Thread.sleep(3000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            salary = i;
        }

    }

    public void mit(int num) {
        synchronized (this) {
            int i = salary - num;
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            salary = i;
        }
    }
}
