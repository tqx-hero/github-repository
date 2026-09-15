package com.spring.import2.config;

import com.spring.import2.dao.UserDao;
import com.spring.import2.service.UserService;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 13:29
 */
@Configuration
@Import({UserDao.class, UserService.class})
public class SpringConfig {


}
