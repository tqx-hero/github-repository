package com.spring.importclass.service;

import com.spring.importclass.dao.IUserDao;
import com.spring.importclass.dao.UserDao;
import org.springframework.context.annotation.DependsOn;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 8:15
 */
//@DependsOn("userDao")
public class UserService implements IUserService {

    private final IUserDao dao;

    public UserService(IUserDao dao) {
        this.dao = dao;
    }

    @Override
    public void say() {
        dao.say();
    }
}
