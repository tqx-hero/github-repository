package com.tqx.spring.dao;

import jakarta.annotation.PostConstruct;
import org.springframework.beans.factory.InitializingBean;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 13:41
 */
public class ServiceDao implements InitializingBean {

    public ServiceDao() {
        System.out.println("Dao实例化");
    }

    @Override
    public void afterPropertiesSet() throws Exception {
        System.out.println("Dao初始化成功，接口");
    }


    @PostConstruct
    public void initDao() {
        System.out.println("PostConstruct dao成功");
    }

    public void init() {
        System.out.println("加载方法的  初始化成功");
    }

}
