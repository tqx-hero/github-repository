package com.spring.sircel;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.context.annotation.Lazy;
import org.springframework.stereotype.Component;

import javax.annotation.Resource;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 10:15
 */
@Component
public class A {
    @Autowired
    private  B b;

    void sayA() {
        System.out.println("A的对象是=" + A.class.getName());
    }
}
