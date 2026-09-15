package com.tqx.thread.aqs;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/17 11:47
 */
public class AQSChild extends AQS {


    public static void main(String[] args) throws InterruptedException {
        AQS aqsChild = new AQSChild();

//        Thread t1 = new Thread(() ->
//                aqsChild.add()
//        );
//        Thread t2 = new Thread(() ->
//                aqsChild.add()
//        );
//
//        t1.start();
//        t2.start();
//        t1.join();
//        t2.join();
//
//        System.out.println(aqsChild.getHead());
    }
}
