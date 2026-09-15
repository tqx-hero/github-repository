package com.spring.c3;

import com.spring.c3.service.IService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class C3ApplicationTests {


    @Autowired
    IService service;

    @Test
    void contextLoads() {
        service.say();
    }

}
