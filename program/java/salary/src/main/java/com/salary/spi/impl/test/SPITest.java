package com.salary.spi.impl.test;

import com.salary.spi.ISPI;
import com.salary.spi.impl.loader.SPIClassLoader;

import java.util.ServiceLoader;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 8:53
 */
public class SPITest {
    public static void main(String[] args) {
        SPIClassLoader classLoader = new SPIClassLoader("D:\\workSpace\\salary-spi\\target\\classes");
        ServiceLoader.load(ISPI.class, classLoader).forEach(ISPI::say);
    }
}
