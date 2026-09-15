package com.spring.c3.service;

import com.spring.c3.dao.UserDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 21:11
 */
@Service
public class CService implements IService {
    @Autowired
    @Qualifier("userDao")
    UserDao userDaos;

    @Override
    public void say() {
        userDaos.say();
        System.out.println(userDaos.toString());
    }
}
