package com.salary.loader;

import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.URL;

/**
 * @author Administrator
 * @version 1.0
 * @description: 通过自定义ClassLoader方式实例化jar包内的class对象
 * @date 2026/3/9 17:18
 */
public class JarClassLoader extends ClassLoader {

    private String filePath;

    public JarClassLoader(String filePath) {
        this.filePath = filePath;
    }


//    //打破双亲委派机制，就是重写loadClass方法，破坏加载类从上到下的流程，直接从本加载器直接findClass
//    @Override
//    public Class<?> loadClass(String name, boolean resolve) throws ClassNotFoundException {
//        Class<?> c;
//        synchronized (getClassLoadingLock(name)) {
//            // First, check if the class has already been loaded
//            c = findLoadedClass(name);
//            if (c == null) {
//                c = findClass(name);
//                if (c == null) {
//                    c = super.loadClass(name, resolve);
//                }
//            }
//        }
//        return c;
//    }

    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        String prefx = "jar:file:";
        String className = prefx + filePath + "!" + "/" + name.replace(".", "/").concat(".class");
        int len;
        byte[] bytes = new byte[1024];
        URL url;
//        FileInputStream fi = new FileInputStream(className);
        try (InputStream is = new URL(className).openStream();
             ByteArrayOutputStream bo = new ByteArrayOutputStream()) {
            while ((len = is.read(bytes)) != -1) {
                bo.write(bytes, 0, len);
            }
            return defineClass(name, bo.toByteArray(), 0, bo.toByteArray().length);
        } catch (Exception e) {
            return null;
        }

    }
}
