package com.spring.beanlife.config;

import com.spring.beanlife.service.BeanService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 9:37
 */
@Configuration
public class SpringConfig {

    @Bean(initMethod = "initMethod",destroyMethod = "destory2")
    public BeanService beanService() {
        return new BeanService();
    }

}
