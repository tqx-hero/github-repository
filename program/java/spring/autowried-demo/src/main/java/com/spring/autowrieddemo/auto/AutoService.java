package com.spring.autowrieddemo.auto;

import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 17:31
 */
@Service
public class AutoService {

    void say(){
        System.out.println("AutoService调用");
    }
}
