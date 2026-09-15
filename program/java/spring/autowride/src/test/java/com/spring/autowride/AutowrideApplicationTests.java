package com.spring.autowride;

import com.spring.autowride.service.IUserService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class AutowrideApplicationTests {

    @Autowired
    IUserService userService;

    @Test
    void contextLoads() {
        userService.say();
    }

}
