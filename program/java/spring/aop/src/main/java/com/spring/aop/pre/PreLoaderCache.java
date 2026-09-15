package com.spring.aop.pre;

import com.spring.aop.aspect.Logs;
import com.spring.aop.cache.CacheLogs;
import com.spring.aop.cache.entry.LogsEntry;
import org.reflections.Reflections;
import org.reflections.scanners.MethodAnnotationsScanner;
import org.reflections.scanners.TypeAnnotationsScanner;
import org.springframework.stereotype.Component;

import java.lang.reflect.Method;
import java.util.Objects;
import java.util.Set;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 20:08
 */
public class PreLoaderCache {

    //指定扫描的包
    private static final String SCAN_PACKAGES = "com.spring.aop.service";

    public static void preLoadCacheLogs() {
        Reflections reflections = new Reflections(SCAN_PACKAGES,
                new MethodAnnotationsScanner(),
                new TypeAnnotationsScanner());
        //缓存有注解的方法
        Set<Method> methodSet = reflections.getMethodsAnnotatedWith(Logs.class);
        if (Objects.nonNull(methodSet)) {
            methodSet.forEach(CacheLogs::getMethodLogs);
            System.out.println("注解方法已加入缓存，数量=" + methodSet.size());
        }

        //缓存有注解的类
        Set<Class<?>> classSet = reflections.getTypesAnnotatedWith(Logs.class);
        if (Objects.nonNull(classSet)) {
            classSet.forEach(CacheLogs::getClassLogs);
            System.out.println("注解类已加入缓存，数量=" + classSet.size());
        }
        System.out.println("缓存完毕");
    }

}
