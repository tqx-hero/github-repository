package com.spring.import3.config;

import com.spring.import3.dao.UserDao;
import com.spring.import3.selector.MyImportSelector;
import com.spring.import3.service.UserService;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 13:29
 */
@Configuration
@Import({MyImportSelector.class})
public class SpringConfig {


}
