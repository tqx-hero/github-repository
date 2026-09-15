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
public class B {
    @Autowired
    private A a;

    public void sayB() {
        System.out.println("B的实例对象=" + B.class.getName());
    }
}
