package com.tqx.spring.config;

import com.tqx.spring.dao.ServiceDao;
import com.tqx.spring.processor.ServicePostProcessor;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 11:41
 */
@Configuration
public class SpringConfig {


    @Bean(initMethod = "init")
    public ServiceDao serviceDao() {
        return new ServiceDao();
    }

}
