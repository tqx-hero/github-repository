package com.spring.dao;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 20:04
 */

public class UserDao implements IUserDao {
    @Override
    public void say() {
        System.out.println("hello");
    }
}
