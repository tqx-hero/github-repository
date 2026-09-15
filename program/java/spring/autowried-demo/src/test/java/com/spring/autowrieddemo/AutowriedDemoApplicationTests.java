package com.spring.autowrieddemo;

import com.spring.autowrieddemo.auto.AutoServiceAutoInject;
import com.spring.autowrieddemo.test.ServiceA;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class AutowriedDemoApplicationTests {

    //    @Autowired
    @Resource
    AutoServiceAutoInject service;

    @Resource
     ServiceA serviceA;

    @Test
    void contextLoads() {
        service.say();
    }

    @Test
    void testAutoServiceAutoInject(@Autowired AutoServiceAutoInject ser) {
        ser.productSay();
    }

    @Test
    void testA(){
        serviceA.say();
    }


}
