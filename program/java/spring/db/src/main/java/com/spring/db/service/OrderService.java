package com.spring.db.service;

import com.spring.db.dao.UserDao;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/11 16:20
 */
@Service
public class OrderService {

    private final UserDao userDao;

    public OrderService(UserDao userDao) {
        this.userDao = userDao;
    }

    @Transactional
    public int insert(Integer id, String name) {
        int i = userDao.insert(id, name);
        return i;
    }

    @Transactional
    public int update(Integer id, String name) {
        int i = userDao.update(id, name);
        return i;
    }

    @Transactional
    public int delete(Integer id) {
        int i = userDao.delete(id);
        return i;
    }

    public Object select(Integer id) {
        Object vo = userDao.select(id);
        return vo;
    }
}
