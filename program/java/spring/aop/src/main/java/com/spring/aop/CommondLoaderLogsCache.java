package com.spring.aop;

import com.spring.aop.pre.PreLoaderCache;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: 预热加载
 * @date 2026/3/10 20:03
 */
@Component
public class CommondLoaderLogsCache implements CommandLineRunner {
    @Override
    public void run(String... args) throws Exception {
        PreLoaderCache.preLoadCacheLogs();
    }
}
