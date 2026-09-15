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
public class ServiceB {

    private final ServiceA a;

    public ServiceB(ServiceA a) {
        this.a = a;
    }

//    public void say() {
//        System.out.println("ServiceB......");
//        a.say();
//    }

    public void sayB() {
        System.out.println("ServiceB..sayB....");
    }

}
