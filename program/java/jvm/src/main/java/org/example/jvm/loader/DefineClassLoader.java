package org.example.jvm.loader;   //在自定义文件加载时一定注意不要带包名


import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 * @author Administrator
 * @version 1.0
 * @description: 测试自定义类加载器
 * @date 2026/3/6 18:35
 */
public class DefineClassLoader {

    public void say() {
//        System.out.println("自定义类加载成功");
//        System.out.println("类加载器为：" + this.getClass().getClassLoader().getClass().getName());


    }

    public static void main(String[] args) {
//        System.out.println("String的类加载器===" + String.class.getClassLoader());
        try {
            Method method = String.class.getMethod("valueOf", int.class);
            Object invoke = method.invoke(String.class, 10);
            System.out.println(invoke);
        } catch (NoSuchMethodException e) {
            throw new RuntimeException(e);
        } catch (InvocationTargetException e) {
            throw new RuntimeException(e);
        } catch (IllegalAccessException e) {
            throw new RuntimeException(e);
        }
    }
}
