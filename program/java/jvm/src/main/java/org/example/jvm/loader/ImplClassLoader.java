package org.example.jvm.loader;

import lombok.SneakyThrows;

import java.io.*;
import java.lang.reflect.InvocationTargetException;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/6 18:40
 */
public class ImplClassLoader extends ClassLoader {

    private String rootPath;

    public ImplClassLoader(String rootPath) {
        this.rootPath = rootPath;
    }

    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        String className = name.replace('.', '/') + ".class";
        String filePath = rootPath + "/" + className;

        byte[] bytes = null;
        try {
            bytes = loadBytes(filePath);
        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }

        Class<?> aClass = defineClass(name, bytes, 0, bytes.length);

        if (Objects.isNull(aClass)) {
            throw new ClassNotFoundException(filePath);
        }
        return aClass;
    }

    private static byte[] loadBytes(String filePath) throws FileNotFoundException {


        try (InputStream in = new FileInputStream(filePath);
             ByteArrayOutputStream bo = new ByteArrayOutputStream();
        ) {
            byte[] bytes = new byte[2048];
            int length = 0;
            while ((length = in.read(bytes)) != -1) {
                bo.write(bytes, 0, length);
            }
            return bo.toByteArray();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }


    public static void main(String[] args) throws ClassNotFoundException, NoSuchMethodException, InvocationTargetException, InstantiationException, IllegalAccessException {
        ImplClassLoader loader = new ImplClassLoader("E:/test/");
        Class<?> aClass = loader.loadClass("DefineClassLoader");
        Object object = aClass.getDeclaredConstructor().newInstance();
        aClass.getMethod("say").invoke(object);
        System.out.println("类加载器验证====" + object.getClass().getClassLoader().getClass().getName());
    }

}
