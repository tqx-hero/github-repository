package com.spring.autowride.config;

import com.spring.autowride.dao.IUserDao;
import com.spring.autowride.dao.UserDao;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 16:15
 */
@Configuration
public class SpringConfig {

    @Bean
    public IUserDao userDaos() {
        UserDao userDao = new UserDao();
        userDao.setName("李四");
        return userDao;
    }
}
