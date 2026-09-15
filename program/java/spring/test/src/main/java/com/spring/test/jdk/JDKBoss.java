package com.spring.test.jdk;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/11 8:42
 */
public class JDKBoss implements IJDKBoss {


    @Override
    public void say(String name) {
        System.out.println("jdk领导接见了" + name);
    }
}
