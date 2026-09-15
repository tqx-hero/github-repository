package com.spring.scope;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class ScopeApplicationTests {

    @Resource
    private ClassA a;

    @Resource
    private ClassA b;

    @Test
    void contextLoads() {
        System.out.println(b==a);   //false

    }

}
