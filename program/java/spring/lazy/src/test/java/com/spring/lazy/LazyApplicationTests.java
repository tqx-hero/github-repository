package com.spring.lazy;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class LazyApplicationTests {
    @Resource
    LazyTest test;

    @Test
    void contextLoads() {
        test.say();

    }

}
