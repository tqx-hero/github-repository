package com.salary.test;

import com.salary.service.ISalaryService;

import java.util.ServiceLoader;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 0:50
 */
public class LoadServiceLoaderList {

    public static ServiceLoader<?> getList(ClassLoader loader, Class<? extends Object> obj) {
        ClassLoader cl = Thread.currentThread().getContextClassLoader();
        ServiceLoader<?> services;
        try {
            Thread.currentThread().setContextClassLoader(loader);
            services = ServiceLoader.load(obj);
        } catch (Exception e) {
            throw new RuntimeException(e);
        } finally {
            Thread.currentThread().setContextClassLoader(cl);
        }
        return services;
    }
}
