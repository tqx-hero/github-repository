package com.example.test.que;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/2/26 11:13
 */
public class ArrayQueueClass {

    public static void main(String[] args) {
        ArrayQueueDemo demo = new ArrayQueueDemo(5);
        boolean add = demo.add("1");
        demo.add("11");
        demo.add("12");
        demo.add("13");
        demo.add("14");
        System.out.println("添加成功？==" + add);
        System.out.println("大小？==" + demo.getSize());
        System.out.println("尾部指针？==" + demo.getRear());
        System.out.println("队列内部集合？==" + demo);

        System.out.println("头部=="+demo.peek());
        demo.del();
        System.out.println("队列内部集合？==" + demo.getFront());
        System.out.println("头部=="+demo.peek());
    }
}
