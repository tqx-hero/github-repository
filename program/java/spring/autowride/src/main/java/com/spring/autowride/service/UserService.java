package com.spring.autowride.service;

import com.spring.autowride.dao.IUserDao;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 16:14
 */
@Service
public class UserService implements IUserService{

    @Autowired
    private IUserDao userDao;

   public void say(){
        System.out.println(userDao.toString());
    }

}
