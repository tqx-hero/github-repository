package com.spring.service.impl;

import com.spring.service.ISPIService;

import java.util.ServiceLoader;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/21 22:20
 */
public class Test {

    public static void main(String[] args) {
        ServiceLoader.load(ISPIService.class)
                .forEach(System.out::println);
    }
}
