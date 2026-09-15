package com.spring.import3.service;

import com.spring.import3.dao.IUserDao;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 13:28
 */
public class UserService implements IUserService {
    @Autowired
    private IUserDao userDao;
    @Override
    public void say() {
        userDao.say();
    }
}
