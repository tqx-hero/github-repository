package org.example.jvm.loader;

import java.io.ByteArrayOutputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * 自定义类加载器：加载本地指定路径的.class文件
 */
public class CustomClassLoader extends ClassLoader {
    // 自定义类加载的根路径
    private String rootPath;

    // 构造方法：指定加载路径，父类加载器默认使用应用类加载器（AppClassLoader）
    public CustomClassLoader(String rootPath) {
        this.rootPath = rootPath;
    }

    /**
     * 核心方法：重写findClass，实现自定义的类查找逻辑
     *
     * @param name 类的全限定名（如 com.example.TestClass）
     * @return 加载后的Class对象
     * @throws ClassNotFoundException 类未找到时抛出
     */
    @Override
    protected Class<?> findClass(String name) throws ClassNotFoundException {
        try {
            // 1. 将全限定名转换为文件路径（如 com.example.TestClass → com/example/TestClass.class）
            String className = name.replace(".", "/") + ".class";
            String filePath = rootPath + "/" + className;

            // 2. 读取.class文件的字节数组
            byte[] classBytes = loadClassBytes(filePath);

            // 3. 调用父类的defineClass方法，将字节数组转换为Class对象（核心步骤）
            // 第一个参数：类全限定名；第二个参数：字节数组；第三个/第四个：字节数组的起始/结束位置
            Class<?> clazz = defineClass(name, classBytes, 0, classBytes.length);
            if (clazz == null) {
                throw new ClassNotFoundException("类加载失败：" + name);
            }
            return clazz;
        } catch (IOException e) {
            throw new ClassNotFoundException("加载类时发生IO异常：" + name, e);
        }
    }

    /**
     * 辅助方法：读取.class文件为字节数组
     */
    private byte[] loadClassBytes(String filePath) throws IOException {
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
        // 1. 创建自定义类加载器实例，指定加载路径
        CustomClassLoader classLoader = new CustomClassLoader("E:/test/");

        // 2. 加载TestClass类（全限定名）
        Class<?> testClass = classLoader.loadClass("DefineClassLoader");

        // 3. 创建实例并调用方法（反射）
        Object instance = testClass.newInstance();
        testClass.getMethod("say").invoke(instance);

        // 验证类加载器：输出自定义类加载器的名称
        System.out.println("类加载器验证：" + testClass.getClassLoader());
    }
}
