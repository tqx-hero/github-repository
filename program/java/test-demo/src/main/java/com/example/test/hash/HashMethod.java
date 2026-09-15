package com.example.test.hash;


/**
 * @author Administrator
 * @version 1.0
 * @description: 定义一个hash算法
 * @date 2026/2/27 10:23
 */
public class HashMethod {
    public static int hash(Object o) {
        // int res = 31 *
        return o != null ? o.hashCode() : 0;
    }

}
