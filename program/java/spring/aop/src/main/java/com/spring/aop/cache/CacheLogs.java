package com.spring.aop.cache;

import com.spring.aop.aspect.Logs;
import com.spring.aop.cache.entry.LogsEntry;

import java.lang.reflect.Method;
import java.util.Map;
import java.util.WeakHashMap;

/**
 * @author Administrator
 * @version 1.0
 * @description: 缓存注解DEMO
 * @date 2026/3/10 19:33
 */
public class CacheLogs {

    private static final Map<Method, LogsEntry> METHOD_LOGS_ENTRY_MAP;
    private static final Map<Class, LogsEntry> CLASS_LOGS_ENTRY_MAP;

    static {
        CLASS_LOGS_ENTRY_MAP = new WeakHashMap<>();
        METHOD_LOGS_ENTRY_MAP = new WeakHashMap<>();
    }


    public static LogsEntry getMethodLogs(Method me) {
        if (METHOD_LOGS_ENTRY_MAP.containsKey(me))
            return METHOD_LOGS_ENTRY_MAP.get(me);
        Logs l = me.getAnnotation(Logs.class);
        if (l != null) {
            LogsEntry entry = new LogsEntry(l.value(), l.desc());
            METHOD_LOGS_ENTRY_MAP.put(me, entry);
            return entry;
        }
        return null;
    }

    public static LogsEntry getClassLogs(Class clazz) {
        if (CLASS_LOGS_ENTRY_MAP.containsKey(clazz))
            return CLASS_LOGS_ENTRY_MAP.get(clazz);
        Logs l = (Logs) clazz.getAnnotation(Logs.class);
        if (l != null) {
            LogsEntry entry = new LogsEntry(l.value(), l.desc());
            CLASS_LOGS_ENTRY_MAP.put(clazz, entry);
            return entry;
        }
        return null;
    }


    public static void clearClassCache() {
        CLASS_LOGS_ENTRY_MAP.clear();
    }

    public static void clearMethodCache() {
        METHOD_LOGS_ENTRY_MAP.clear();
    }

    public static void clearAllCache() {
        clearMethodCache();
        clearClassCache();
    }

}
