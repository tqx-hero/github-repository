package com.spring.factorybean.dao;

import org.springframework.stereotype.Repository;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 21:10
 */
@Repository
public class UserDao implements IUserDao {
    @Override
    public void say() {
        System.out.println("hll");
    }
}
