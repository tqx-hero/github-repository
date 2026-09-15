package com.spring.import2;

import com.spring.import2.service.IUserService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class Import2ApplicationTests {

    @Autowired
    private IUserService userService;

    @Test
    void contextLoads() {
        userService.say();
    }

}
