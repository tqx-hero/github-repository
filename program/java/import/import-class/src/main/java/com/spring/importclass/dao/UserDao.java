package com.spring.importclass.dao;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 8:16
 */

import com.spring.importclass.property.AppProperties;
import org.springframework.boot.context.properties.bind.Binder;
import org.springframework.context.EnvironmentAware;
import org.springframework.core.env.Environment;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

public class UserDao  implements IUserDao{

//    private Environment environment;


    @Resource
    private AppProperties pro;

    @Override
    public void say() {
//        List list = Binder.get(environment).bind("my.selects.list", List.class).orElse(List.of());
//        list.forEach(System.out::println);
        pro.getList().forEach(System.out::println);
        pro.getScore().entrySet().forEach(System.out::println);
        System.out.println("UserDao say");
    }

}
