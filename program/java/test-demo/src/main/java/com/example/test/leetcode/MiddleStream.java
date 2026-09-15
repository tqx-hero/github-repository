package com.example.test.leetcode;

import java.io.IOException;
import java.io.InputStream;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 获取数据流的中位数
 * @date 2026/3/1 9:58
 */
public class MiddleStream {


    /**
     * 获取数据流的中位数
     *
     * @param m
     * @return
     */
    public static int middle(MediaStream m) {
        int middle = 0;
        //判断两个堆内数据多少
        int leftSize = Objects.nonNull(m.left) ? m.left.size : 0;
        int rightSize = Objects.nonNull(m.right) ? m.right.size : 0;
        if (leftSize > rightSize) {
            middle = m.left.getTop();
        } else {
            middle = (m.right.getTop() + m.left.getTop()) >> 1;
        }
        return middle;
    }


    public static void main(String[] args) throws IOException {
        InputStream stream = System.in;
        StringBuilder input = new StringBuilder();
        MediaStream mediaStream = new MediaStream();
        int i;
        while ((i = stream.read()) != -1) {
            char c = (char) i;
            // 处理退出指令
            if (input.toString().equalsIgnoreCase("exit") && (c == '\n' || c == '\r')) {
                System.out.println("\n程序退出！");
                break;
            }
            // 处理退格（ASCII 8）
            if (c == 8 && input.length() > 0) {
                input.deleteCharAt(input.length() - 1);
                // 控制台回退并清除字符：\b 回退，空格覆盖，\b 再回退
                System.out.print("\b \b");
                continue;
            }
            if (!(c == '\n' || c == '\r')) {
                input.append(c);
                mediaStream.init(Integer.parseInt(String.valueOf(c)));
                int middle = middle(mediaStream);
                System.out.println("输入==" + c);
                System.out.println("数据流==" + mediaStream);
                System.out.println("数据流的中位数=" + middle);
            }
        }
    }

}
