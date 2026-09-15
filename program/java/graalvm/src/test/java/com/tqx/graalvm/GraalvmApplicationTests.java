package com.tqx.graalvm;

import com.tqx.graalvm.service.impl.UserService;
import jakarta.annotation.Resource;
import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
class GraalvmApplicationTests {

    @Resource
    private UserService service;

    @Test
    void contextLoads() {

        service.select("tqx");

        service.update("123");
    }

}
