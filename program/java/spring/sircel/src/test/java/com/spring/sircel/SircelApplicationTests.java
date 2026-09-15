package com.spring.sircel;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class SircelApplicationTests {


    @Resource
    private A a;
    @Resource
    private B b;

    @Test
    void contextLoads() {
        a.sayA();
        b.sayB();
    }

}
