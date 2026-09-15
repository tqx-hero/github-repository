package com.spring.depend.a;

import org.springframework.context.annotation.DependsOn;
import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 9:25
 */
@Component
@DependsOn("classB")   //这里是注入bean的名字，驼峰形式
public class ClassA {

    public ClassA() {
        System.out.println("ClassA()加载");
    }
}
