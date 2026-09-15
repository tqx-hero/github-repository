package com.spring.importclass.config;

import com.spring.importclass.bean.MyBeanDefinition;
import com.spring.importclass.dao.IUserDao;
import com.spring.importclass.dao.UserDao;
import com.spring.importclass.selector.MyImportSelector;
import com.spring.importclass.service.IUserService;
import com.spring.importclass.service.UserService;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 8:25
 */
@Configuration
//@Import({MyImportSelector.class})
@Import({MyBeanDefinition.class})
public class SpringConfig {

//    @Bean
//    public IUserService userService(IUserDao userDao) {
//        return new UserService(userDao);
//    }
//
//    @Bean
//    public IUserDao userDao() {
//        return new UserDao();
//    }
}
