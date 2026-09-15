package com.spring.conditional;

import com.spring.conditional.service.DBIService;
import com.spring.conditional.service.MysqlService;
import com.spring.conditional.service.OracleService;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import javax.annotation.Resource;

@SpringBootTest
class ConditionalApplicationTests {

    @Resource
    private DBIService service;  //实现类均实现该接口，且两者仅会加载一个，这里用到了java的多态性

    @Test
    void contextLoads() {
//        System.out.println("oracleService====================" + oracleService);
//        System.out.println("mysqlService====================" + mysqlService);
        System.out.println("加载的驱动类型====================" + service);
    }

}
