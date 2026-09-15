package com.spring.beanlife;

import com.spring.beanlife.service.BeanService;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class BeanLifeApplicationTests {

    @Resource
    private BeanService service;

    @Test
    void contextLoads() {

        System.out.println(service.getClass());

    }

}
