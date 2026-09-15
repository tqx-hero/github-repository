package com.spring.lazy;

import org.springframework.context.annotation.Lazy;
import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 9:31
 */
@Component
@Lazy
public class ClassLazy {

    public ClassLazy() {
        System.out.println("ClassLazy加载");
    }
}
