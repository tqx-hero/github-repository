package com.spring.depend.a;

import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 9:26
 */
@Component
public class ClassB {
    public ClassB() {
        System.out.println("ClassB()加载");
    }
}
