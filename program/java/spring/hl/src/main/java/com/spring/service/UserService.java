package com.spring.service;

import com.spring.dao.IUserDao;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 20:04
 */
public class UserService {

    IUserDao dao;


    public void say() {
        dao.say();
    }
}
