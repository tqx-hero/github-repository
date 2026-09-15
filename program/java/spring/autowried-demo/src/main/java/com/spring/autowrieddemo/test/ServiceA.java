package com.spring.autowrieddemo.test;

import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 18:36
 */
@Service
public class ServiceA {


    @Resource
    private  ServiceB b;

//    public ServiceA(ServiceB b) {
//        this.b = b;
//    }

   public void say(){
        System.out.println("ServiceA......");
        b.sayB();
    }
}
