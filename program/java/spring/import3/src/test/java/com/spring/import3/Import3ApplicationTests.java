package com.spring.import3;

import com.spring.import3.service.IUserService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class Import3ApplicationTests {

    @Autowired
    IUserService userService;

    @Test
    void contextLoads() {
        userService.say();
    }

}
