package com.spring.boot;

import com.spring.boot.service.IService;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class BootApplication {

    public static void main(String[] args) {
        ConfigurableApplicationContext run = SpringApplication.run(BootApplication.class, args);
        IService service = run.getBean(IService.class);
        service.say();
    }

}
