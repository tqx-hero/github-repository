package com.spring.importclass;

import com.spring.importclass.service.IUserService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class ImportClassApplicationTests {

    @Test
    void contextLoads(@Autowired IUserService userService) {
        userService.say();
    }

}
