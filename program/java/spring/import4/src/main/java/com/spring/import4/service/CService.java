package com.spring.import4.service;

import com.spring.import4.dao.IUserDao;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 21:11
 */
//@Service
public class CService implements IService {
    @Autowired
    IUserDao userDao;

    @Override
    public void say() {
        userDao.say();
    }
}
