package com.tqx.bytes;

import java.nio.ByteBuffer;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 19:01
 */
public class ByteBufferDemo {
    public static void main(String[] args) {
        //在直接内存中创建一个byte[]缓冲区
//        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);
        //在堆内创建一个byte[]缓冲区
        ByteBuffer buffer = ByteBuffer.allocate(1024);

        System.out.println("index:" + buffer.position() + " limit: " + buffer.limit() + " capacity : " + buffer.capacity());

        //放入缓冲区
        buffer.put("abc".getBytes());
        System.out.println("index:" + buffer.position() + " limit: " + buffer.limit() + " capacity : " + buffer.capacity());
        //翻转指针，index=0,limit=最后一个元素，用于读取数据
        buffer.flip();
        for (int i = buffer.position(); i < buffer.limit(); i++) {
            System.out.println(buffer.get());
        }
        System.out.println("index:" + buffer.position() + " limit: " + buffer.limit() + " capacity : " + buffer.capacity());
        //将剩余数据靠左排列对齐，index=最后一位元素，limit=数组最末位置，用于读取完成后继续放入
        buffer.compact();
        buffer.put("def".getBytes());
        System.out.println("index:" + buffer.position() + " limit: " + buffer.limit() + " capacity : " + buffer.capacity());


    }
}
