package com.spring.service.impl;

import com.spring.service.ISPIService;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 12:41
 */
public class SPIService implements ISPIService {
    @Override
    public void say() {
        System.out.println("SPI Service 加载成功");
    }
}
