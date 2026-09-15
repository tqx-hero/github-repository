package com.salary.loader;

import java.io.*;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Objects;
import java.util.jar.JarEntry;
import java.util.jar.JarOutputStream;
import java.util.jar.Manifest;

/**
 * @author Administrator
 * @version 1.0
 * @description: 读取jar包中的myClass文件
 * @date 2026/3/9 17:43
 */
public class JarInputMyClassClassLoader extends ClassLoader {

    private String fileName;

    public JarInputMyClassClassLoader(String fileName) {
        this.fileName = fileName;
    }

    @Override
    protected Class<?> findClass(String name) {
        String prex = "jar:file:";
        String className = prex + fileName + "!/" + name.replace('.', '/').concat(".myClass");
        int len;
        byte[] bytes = new byte[1024];
        InputStream is = null;
        URL myURL = null;
        ByteArrayOutputStream os = null;
        try {
            myURL = new URL(className);
            is = myURL.openStream();
            os = new ByteArrayOutputStream();
            //解密，对应文件中多增加一位的操作，先把第一个数据拿出来
            is.read();
            while ((len = is.read(bytes)) != -1) {
                os.write(bytes, 0, len);
            }
            return super.defineClass(name, os.toByteArray(), 0, os.toByteArray().length);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        } finally {
            if (Objects.nonNull(is)) {
                try {
                    is.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
            if (Objects.nonNull(os)) {
                try {
                    os.close();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public static void main(String[] args) throws ClassNotFoundException {
        JarInputMyClassClassLoader classLoader = new JarInputMyClassClassLoader("D:\\salary-api\\salary-spi-1.0-SNAPSHOT.jar");
        Class<?> aClass = classLoader.loadClass("com.salary.service.impl.SalaryService");
    }
}
