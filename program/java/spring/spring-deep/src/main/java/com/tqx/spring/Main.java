package com.tqx.spring;

import com.tqx.spring.config.SpringConfig;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.AnnotationConfigApplicationContext;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 11:39
 */
@SpringBootApplication
public class Main {

    public static void main(String[] args) {
        AnnotationConfigApplicationContext context = new AnnotationConfigApplicationContext(Main.class);
        System.out.println(context.getBean("userService").getClass().getName());
    }
}
