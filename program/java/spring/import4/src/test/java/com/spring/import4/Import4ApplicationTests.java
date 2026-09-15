package com.spring.import4;

import com.spring.import4.service.IService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.stereotype.Service;

@SpringBootTest
class Import4ApplicationTests {

    @Autowired
    IService iService;

    @Test
    void contextLoads() {
        iService.say();
    }

}
