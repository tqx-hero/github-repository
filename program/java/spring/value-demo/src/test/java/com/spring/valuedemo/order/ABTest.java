package com.spring.valuedemo.order;

import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.context.annotation.Bean;
import org.springframework.core.annotation.Order;

import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 20:01
 */
@SpringBootTest(classes = ABTest.class)
public class ABTest {

    @Bean
    @Order(1)
    public  A a(){
        return new A();
    }
    @Bean
    @Order(10)
    public  B b(){
        return new B();
    }

    @Test
    void test(@Autowired List<I> i){
        for (I s : i) {
            s.say();
        }
    }
}
