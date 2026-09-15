package com.spring.lazy;

import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 9:31
 */
@Component
public class ClassHungry {

    public ClassHungry() {
        System.out.println("ClassHungry加载");
    }
}
