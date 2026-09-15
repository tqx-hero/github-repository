package com.spring.db;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.cglib.core.DebuggingClassWriter;
import org.springframework.context.ConfigurableApplicationContext;
import org.springframework.context.annotation.EnableAspectJAutoProxy;

import java.io.File;

@SpringBootApplication
@EnableAspectJAutoProxy(exposeProxy = true)
public class DbApplication {

    public static void main(String[] args) {
        String savePath = System.getProperty("user.dir") + File.separator + "cglib_proxy_classes";
        System.setProperty(DebuggingClassWriter.DEBUG_LOCATION_PROPERTY, savePath);
        ConfigurableApplicationContext context = SpringApplication.run(DbApplication.class, args);
        System.out.println(context.getBean("userService").getClass().getName());
    }

}
