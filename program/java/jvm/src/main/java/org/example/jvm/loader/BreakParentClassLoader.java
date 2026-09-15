package org.example.jvm.loader;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * 打破双亲委派的自定义类加载器
 * 核心：重写loadClass()，优先加载自定义路径的类
 */
public class BreakParentClassLoader extends ClassLoader {
    // 自定义类加载路径
    private String classPath;

    // 构造方法：指定类加载路径，父加载器默认使用应用类加载器
    public BreakParentClassLoader(String classPath) {
        this.classPath = classPath;
    }

    /**
     * 重写loadClass()，打破双亲委派
     * @param name 类全限定名
     * @param resolve 是否解析类（链接阶段）
     */
    @Override
    protected Class<?> loadClass(String name, boolean resolve) throws ClassNotFoundException {
        synchronized (getClassLoadingLock(name)) {
            // 1. 检查类是否已加载（缓存）
            Class<?> clazz = findLoadedClass(name);

            // 2. 未加载则进入自定义加载逻辑
            if (clazz == null) {
                // 核心规则：核心类（java.lang.*）仍走双亲委派，避免SecurityException
                if (name.startsWith("java.lang.")) {
                    // 核心类委托父加载器加载
                    clazz = super.loadClass(name, resolve);
                } else {
                    // 非核心类：优先自己加载（打破双亲委派）
                    try {
                        // 调用自定义findClass加载
                        clazz = findClass(name);
                    } catch (ClassNotFoundException e) {
                        // 自己加载失败，再委托父加载器（兜底）
                        clazz = super.loadClass(name, resolve);
                    }
                }
            }

            // 3. 若需要解析，执行链接阶段
            if (resolve) {
                resolveClass(clazz);
            }
            return clazz;
        }
    }

    /**
     * 自定义类查找逻辑：读取指定路径的.class文件为字节数组，生成Class对象
     */
    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        try {
            // 转换类名到文件路径（com.example.Test → com/example/Test.class）
            String fileName = name.replace(".", "/") + ".class";
            String filePath = classPath + "/" + fileName;

            // 读取.class文件字节数组
            byte[] classBytes = loadClassFromFile(filePath);

            // 调用defineClass注入JVM，生成Class对象（核心方法，不可重写）
            return defineClass(name, classBytes, 0, classBytes.length);
        } catch (IOException e) {
            throw new ClassNotFoundException("类加载失败：" + name, e);
        }
    }

    /**
     * 辅助方法：读取文件为字节数组
     */
    private byte[] loadClassFromFile(String filePath) throws IOException {
        try (InputStream is = new FileInputStream(filePath);
             ByteArrayOutputStream bos = new ByteArrayOutputStream()) {
            byte[] buffer = new byte[1024];
            int len;
            while ((len = is.read(buffer)) != -1) {
                bos.write(buffer, 0, len);
            }
            return bos.toByteArray();
        }
    }

    // 测试方法
    public static void main(String[] args) throws Exception {
        // 1. 准备：将TestClass.class放在D:/break_class/路径下（非classpath）
        BreakParentClassLoader classLoader = new BreakParentClassLoader("E:/test/");

        // 2. 加载自定义类（优先使用当前加载器，而非父加载器）
        Class<?> testClass = classLoader.loadClass("DefineClassLoader");

        // 3. 反射调用方法，验证加载器
        Object instance = testClass.newInstance();
        testClass.getMethod("say").invoke(instance);

        // 输出类加载器：确认是自定义加载器（而非父加载器）
        System.out.println("类加载器：" + testClass.getClassLoader().getClass().getName());
    }
}
