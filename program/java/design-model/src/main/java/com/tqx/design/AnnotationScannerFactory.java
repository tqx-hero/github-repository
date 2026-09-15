package com.tqx.design;

import com.tqx.design.factory_strategy.SuperMarketAnstractBeanFactory;
import com.tqx.design.factory_strategy.ann.Inject;
import com.tqx.design.factory_strategy.aop.AbstractCallBack;
import com.tqx.design.factory_strategy.aop.AopProxy;
import com.tqx.design.factory_strategy.processor.BeanProcessor;
import com.tqx.design.factory_strategy.proxy.ProxyFactory;
import com.tqx.design.factory_strategy.util.AnnotationUtils;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.net.URLDecoder;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: 扫描该包及其子包下面含有指定注解的类，为动态代理提供class
 * @date 2026/3/21 23:37
 */
public class AnnotationScannerFactory extends SuperMarketAnstractBeanFactory {

    private static final Set<String> CLASS_NAME_SETS;
    private static final Map<String, Object> OBJECT_MAP;
    private static ReentrantLock lock;

    private ProxyFactory proxyFactory;

    public ProxyFactory setProxyFactory(ProxyFactory proxyFactory) {
        this.proxyFactory = proxyFactory;
        return proxyFactory;
    }

    static {
        CLASS_NAME_SETS = new HashSet<>(32);
        OBJECT_MAP = new ConcurrentHashMap<>(32);
        lock = new ReentrantLock();
    }

    {
        proxyFactory = AopProxy.getInstance().
                setBack(AbstractCallBack.getInstance()
                        .setProcessor(BeanProcessor.getInstance()));
    }

    @Override
    public Object getBean(String className) {
        return OBJECT_MAP.get(className);
    }


    private static class ScannerInnerClass {
        private static final AnnotationScannerFactory INSTANCE = new AnnotationScannerFactory();
    }

    public static AnnotationScannerFactory getInstance() {
        return ScannerInnerClass.INSTANCE;
    }

    public Set<String> getClassSet() {
        return CLASS_NAME_SETS;
    }

    private AnnotationScannerFactory() {
        //加载自定义注解，并将class缓存到SET集合
        getClassSetByAnnotation();
    }

    public static void main(String[] args) {
        AnnotationScannerFactory scanner = new AnnotationScannerFactory();
//        scanner.getClassSetByAnnotation();
        CLASS_NAME_SETS.forEach(System.out::println);
        OBJECT_MAP.keySet().forEach(s -> System.out.println(OBJECT_MAP.get(s)));
    }

    public void getClassSetByAnnotation() {
        ClassLoader loader = this.getClass().getClassLoader();
        String aPackage = this.getClass().getPackage().getName().replaceAll("\\.", "/");
        try {
            Enumeration<URL> resources = loader.getResources(aPackage);
            while (resources.hasMoreElements()) {
                URL url = resources.nextElement();
                String protocol = url.getProtocol();
                if ("file".equals(protocol)) {
                    String filePath = URLDecoder.decode(url.getFile(), StandardCharsets.UTF_8);
                    loadBaseFiles(loader, filePath, aPackage);
                }
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    void loadBaseFiles(ClassLoader loader, String filePath, String aPackage) {
        File file = new File(filePath);
        if (!file.exists()) {
            return;
        }
        //是目录，继续遍历
        if (file.isDirectory()) {
            File[] files = file.listFiles();
            if (Objects.nonNull(files) && files.length > 0) {
                for (int i = 0; i < files.length; i++) {
                    loadBaseFiles(loader, files[i].getPath(), aPackage);
                }
            }
        }
        //是一个普通class文件
        else if (file.canRead() && file.isFile() && file.getName().endsWith(".class")) {
            Class<?> aClass;
            try {
                StringBuilder builder = new StringBuilder(aPackage);
                String str = builder
                        .append(filePath.replaceAll("\\\\", "/")
                                .split(aPackage)[1].split(".class")[0])
                        .toString()
                        .replaceAll("/", ".");
                aClass = loader.loadClass(str);
            } catch (ClassNotFoundException e) {
                throw new RuntimeException(e);
            }
            //仅写了一种类型，可以运用集合形式分成多种注解形式继续遍历
//            if (aClass.isAnnotationPresent(SuperMarket.class)) {
            if (!aClass.isAnnotation() && AnnotationUtils.contaions(aClass, Inject.class)) {
                if (!CLASS_NAME_SETS.contains(aClass.getSimpleName())) {
                    String beanName = aClass.getSimpleName().substring(0, 1).toLowerCase()
                            + aClass.getSimpleName().substring(1);
                    try {
                        lock.lock();
                        CLASS_NAME_SETS.add(beanName);
                        //判断需不需要注入代理
                        OBJECT_MAP.put(beanName
                                , ProxyFactory.needAop(aClass) ?
                                        proxyFactory.createProxy(aClass) : aClass.getDeclaredConstructor().newInstance()
                        );
                    } catch (Exception e) {

                    } finally {
                        if (lock.isHeldByCurrentThread()) {
                            lock.unlock();
                        }
                    }
                }
            }
        }

    }

}
