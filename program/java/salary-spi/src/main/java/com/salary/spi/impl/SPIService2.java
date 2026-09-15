package com.salary.spi.impl;

import com.salary.spi.ISPI;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 9:01
 */
public class SPIService2 implements ISPI {
    @Override
    public void say() {
        System.out.println("远程调用SPI服务2.....");
    }
}
