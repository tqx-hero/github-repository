package com.tqx.spring;

import com.tqx.spring.dao.ServiceDao;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class SpringDeepApplication {

    public static void main(String[] args) {
        ConfigurableApplicationContext run = SpringApplication.run(SpringDeepApplication.class, args);
        System.out.println(run.getBean("userService").getClass().getName());
    }

}
