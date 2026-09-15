package com.tqx.file;

import java.io.File;

/**
 * @author Administrator
 * @version 1.0
 * @description: 遍历文件
 * 返回文件路径下所有文件以及文件大小
 * @date 2026/4/10 9:03
 */
public class IteratorFiles {

    public static void orderFiles(String fileName) {
        File file = new File(fileName);
        order(file);
    }

    private static void order(File file) {
        if (file.exists()) {
            System.out.println("文件名：[" + file.getName() + "],大小：[" + file.length() / 1024.00 + "KB");
            if (!file.isDirectory())
                return;
            File[] files = file.listFiles();
            for (File f : files) {
                order(f);
            }
        }
    }

    public static void main(String[] args) {
        String fileName = "E:\\KuGou";
        IteratorFiles.orderFiles(fileName);
    }

}
