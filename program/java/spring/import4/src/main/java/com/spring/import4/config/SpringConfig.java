package com.spring.import4.config;

import com.spring.import4.bean.MyBeanDefinition;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

/**
 * @author Administrator
 * @version 1.0
 * @description:  使用@configuration + @Bean方式注入spring
 * @date 2026/3/7 22:10
 */
@Configuration
@Import(MyBeanDefinition.class)
public class SpringConfig {


//    @Bean
//    IUserDao getIUserDao() {
//        System.out.println("getIUserDao");
//        return new UserDao();
//    }
}
