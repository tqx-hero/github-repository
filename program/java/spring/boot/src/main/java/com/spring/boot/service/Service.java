package com.spring.boot.service;

import com.spring.boot.dao.IUserDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 21:11
 */
@Component
public class Service implements IService {
    @Autowired
    IUserDao userDao;

    @Override
    public void say() {
        userDao.say();
    }
}
