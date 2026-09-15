package com.salary.loader;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 13:20
 */
public class SalaryClassLoader extends ClassLoader {
    private String filePath;

    public SalaryClassLoader(String filePath) {
        this.filePath = filePath;
    }

    @Override
    public Class<?> findClass(String name) {
        int len;
        String className = filePath + "\\" + name.replace('.', '\\').concat(".myClass");
        byte[] bytes = new byte[1024];
        try (FileInputStream fi = new FileInputStream(className);
             ByteArrayOutputStream os = new ByteArrayOutputStream()) {
            //解密，对应文件中多增加一位的操作，先把第一个数据拿出来
            fi.read();
            while ((len = fi.read(bytes)) != -1) {
                os.write(bytes, 0, len);
            }
            bytes = os.toByteArray();
            return this.defineClass(name, bytes, 0, bytes.length);
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
