package com.spring.beanlife.service;

import org.springframework.beans.factory.DisposableBean;
import org.springframework.beans.factory.InitializingBean;

import javax.annotation.PostConstruct;
import javax.annotation.PreDestroy;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 9:36
 */
public class BeanService implements InitializingBean, DisposableBean {
    @Override
    public void destroy() throws Exception {
        System.out.println("Bean销毁成功，接口形式");
    }

    @PreDestroy
    public void destoryBean() {
        System.out.println("Bean销毁，基于注解");
    }

    //1、初始化完成后的回调函数
    @Override
    public void afterPropertiesSet() throws Exception {
        System.out.println("Bean初始化成功-接口形式");
    }

    //2、基于注解形式回调
    @PostConstruct
    public void initSuccess() {
        System.out.println("注解形式回调加载成功");
    }

    //3、基于@Bean的initMethod变量指定加载方法
    public void initMethod() {
        System.out.println("Bean的加载方法回调成功");
    }

    public void destory2() {
        System.out.println("Bean销毁成功，destoryMethod属性");
    }
}
