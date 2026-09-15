package com.spring.lazy;

import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 9:32
 */
@Component
public class LazyTest {

    private final ClassLazy lazy;

    public LazyTest(ClassLazy lazy) {
        this.lazy = lazy;
    }

    public void say() {
        System.out.println("say");
    }
}
