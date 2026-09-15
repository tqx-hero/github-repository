package com.spring.conditional.config;

import com.spring.conditional.condition.ISInjectMysql;
import com.spring.conditional.condition.ISInjectOracle;
import com.spring.conditional.service.MysqlService;
import com.spring.conditional.service.OracleService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Conditional;
import org.springframework.context.annotation.Configuration;

/**
 * @author Administrator
 * @version 1.0
 * @description: 根据加载驱动的类型来决定注入哪个实例
 * @date 2026/3/9 11:50
 */
@Configuration
public class SpringConfig {

    @Bean
    @Conditional(ISInjectMysql.class)
    public MysqlService conditionService() {
        return new MysqlService();
    }

    @Bean
    @Conditional(ISInjectOracle.class)
    public OracleService oracleService() {
        return new OracleService();
    }
}
