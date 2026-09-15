package com.spring.c3.config;

import com.spring.c3.dao.IUserDao;
import com.spring.c3.dao.UserDao;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * @author Administrator
 * @version 1.0
 * @date 2026/3/7 22:10
 */
@Configuration
public class SpringConfig {

    @Bean
    public UserDao userDaos(){
        UserDao dao = new UserDao();
        dao.setName("李四");
        return dao;
    }

}
