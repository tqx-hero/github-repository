package com.spring.aop.impl;

import com.spring.aop.AopApplication;
import com.spring.aop.service.IUserservice;
import jakarta.annotation.Resource;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.EnableAspectJAutoProxy;


@SpringBootTest(classes = AopApplication.class)
@EnableAspectJAutoProxy(proxyTargetClass = true)
class AopApplicationTests {

    @Resource
    private IUserservice userService;

    @Test
    void contextLoads() throws InterruptedException {
//        userService.add();
//        int i = 5;
//        while (i > 0) {
            userService.add();
//            userService.update(1);
//        userService.query();
//            Thread.sleep(3000);
//            i--;
//        }
//        userService.delete();
    }

}
