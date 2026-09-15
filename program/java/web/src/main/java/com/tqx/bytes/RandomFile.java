package com.tqx.bytes;

import java.io.File;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/22 12:23
 */
public class RandomFile {

    public static void main(String[] args) throws IOException {
        String filePath = "E:\\test\\test.txt";
        RandomAccessFile rw = new RandomAccessFile(new File(filePath), "rw");

//        rw.write("abc".getBytes());

        FileChannel channel = rw.getChannel();
        MappedByteBuffer map = channel.map(FileChannel.MapMode.READ_WRITE, 0, 2048);
        map.put("def123444".getBytes());

//        System.out.println(map.position());
        map.flip();

        map.force();

        rw.seek(0);

//        System.out.println(map.position());

        ByteBuffer buffer = ByteBuffer.allocate(2048);
        channel.read(buffer);

        buffer.flip();

        for (int i = 0; i < buffer.limit(); i++) {
            System.out.println((char) buffer.get(i));
        }

    }
}
