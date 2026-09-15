package com.salary.spi.impl.loader;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 8:57
 */
public class SPIClassLoader extends ClassLoader {

    private String filePath;

    public SPIClassLoader(String filePath) {
        this.filePath = filePath;
    }

    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        String fileName = filePath + "/" + name.replace(".", "/").concat(".class");
        int len;
        byte[] bytes = new byte[1024];
        try (FileInputStream fi = new FileInputStream(fileName);
             ByteArrayOutputStream bo = new ByteArrayOutputStream()) {
            while ((len = fi.read(bytes)) != -1) {
                bo.write(bytes, 0, len);
            }
            return defineClass(name, bo.toByteArray(), 0, bo.toByteArray().length);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return super.findClass(name);
    }
}
