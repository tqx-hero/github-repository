package com.tqx.design.factory_strategy;

import java.lang.reflect.InvocationTargetException;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.locks.ReentrantLock;

/**
 * @author Administrator
 * @version 1.0
 * @description: SPI机制实现创建对象实例，并缓存到集合中
 * @date 2026/3/21 21:42
 */
public class SuperMarketFactory implements SuperMarketAbstractFactory {

    private static final Map<String, SuperMartStrategy> SUPER_MART_STRATEGY_MAP;
    private static final Set<String> SUPER_MART_STRATEGY_NAMES;
    private static ReentrantLock lock;

    private String name;


    private static class SuperMarketInnerClass {
        private static final SuperMarketFactory INSTANCE = new SuperMarketFactory();
    }

    static {
        SUPER_MART_STRATEGY_MAP = new ConcurrentHashMap<>(32);
        SUPER_MART_STRATEGY_NAMES = new HashSet<>(32);
        lock = new ReentrantLock();
    }

    {
        init();
    }

    //定义单例
    public static SuperMarketFactory getInstance() {
        return SuperMarketInnerClass.INSTANCE;
    }

    private SuperMarketFactory() {
    }

    public SuperMarketFactory setName(String name) {
        this.name = name;
        return this;
    }

    //SPI实现加载指定接口实现类
    private void init() {
        ServiceLoader.load(SuperMartStrategy.class)
                .forEach(s -> {
                    Class<? extends SuperMartStrategy> a = s.getClass();
                    if (Objects.nonNull(a) && !SUPER_MART_STRATEGY_NAMES.contains(a.getSimpleName())) {
                        try {
                            String simpleName = a.getSimpleName();
                            simpleName = simpleName.substring(0, 1)
                                    .toLowerCase()
                                    .concat(simpleName.substring(1, simpleName.length()));
                            lock.lock();
                            SUPER_MART_STRATEGY_MAP.put(simpleName, a.getDeclaredConstructor().newInstance());
                            SUPER_MART_STRATEGY_NAMES.add(simpleName);
                        } catch (InstantiationException e) {
                            throw new RuntimeException(e);
                        } catch (IllegalAccessException e) {
                            throw new RuntimeException(e);
                        } catch (InvocationTargetException e) {
                            throw new RuntimeException(e);
                        } catch (NoSuchMethodException e) {
                            throw new RuntimeException(e);
                        } finally {
                            if (lock.isHeldByCurrentThread()) {
                                lock.unlock();
                            }
                        }
                    }
                });
    }

    @Override
    public SuperMartStrategy getSuperMartStrategy() {
        return SUPER_MART_STRATEGY_NAMES.contains(this.name) ? SUPER_MART_STRATEGY_MAP.get(this.name) : null;
    }
}
