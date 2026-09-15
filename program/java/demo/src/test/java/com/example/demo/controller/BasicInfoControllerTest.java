package com.example.demo.controller;

import com.example.demo.entity.BasicInfo;
import com.example.demo.entity.Result;
import com.example.demo.service.BasicInfoService;
import lombok.extern.slf4j.Slf4j;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

@SpringBootTest
@Slf4j
class BasicInfoControllerTest {

    @Autowired
    private BasicInfoService basicInfoService;

    @Test
    void add() {
        BasicInfo info = new BasicInfo(1, "张三");
        System.out.println("info = " + info.toString());
        Result<String> result = basicInfoService.add(info);
        System.out.println("result = " + result.toString());
    }
}