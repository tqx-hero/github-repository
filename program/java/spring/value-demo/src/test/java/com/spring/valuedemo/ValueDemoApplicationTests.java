package com.spring.valuedemo;

import com.spring.valuedemo.pojo.ValueTest;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.Bean;

import javax.annotation.Resource;

@SpringBootTest
class ValueDemoApplicationTests {







    @Test
    void contextLoads(@Autowired ValueTest v) {
        System.out.println(v.getName() + ":" + v.getAge());
    }

}
