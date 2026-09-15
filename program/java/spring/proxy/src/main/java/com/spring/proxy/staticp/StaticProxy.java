package com.spring.proxy.staticp;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 23:02
 */
public class StaticProxy extends Boss {

    @Override
    public void metting(String name) {
        if (name.equals("张三")) {
            super.metting(name);
        }
    }
}
