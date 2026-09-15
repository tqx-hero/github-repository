package com.spring.db.service;

import com.spring.db.dao.UserDao;
import jakarta.annotation.Resource;
import org.springframework.aop.framework.AopContext;
import org.springframework.jdbc.datasource.DataSourceTransactionManager;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.transaction.support.TransactionSynchronizationManager;

import javax.sql.DataSource;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/11 15:39
 */
@Service
public class UserService {

    private final UserDao userDao;
    private final OrderService orderService;

    @Resource
    private DataSource dataSource;

    public UserService(OrderService orderService, UserDao userDao) {
        this.orderService = orderService;
        this.userDao = userDao;
    }

    @Transactional
    public int insert(Integer id, String name) {
        int i = userDao.insert(id, name);
        int i1 = 1 / 0;
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

    @Transactional
    public int mixedService() throws InterruptedException {
        orderService.insert(11, "zhangsan");
//        userService.update(2, "zhangsan1");
//        insert(3, "夏侯渊");
//        Map<Object, Object> resourceMap = TransactionSynchronizationManager.getResourceMap();
//        Object sourceValue = null;
//        for (Map.Entry<Object, Object> entry : resourceMap.entrySet()) {
//            sourceValue = entry.getValue();
//            break;
//        }
//        DataSource dataSource = transactionManager.getDataSource();
//        Object finalSourceValue = sourceValue;
        UserService proxy = (UserService) AopContext.currentProxy();
        Object finalSourceValue = TransactionSynchronizationManager.getResource(dataSource);
        Thread tl = new Thread(() -> {
            TransactionSynchronizationManager.bindResource(dataSource, finalSourceValue);
            proxy.insert(22, "name");
        }
        );
        tl.start();
        tl.join();

        return 0;
    }

}
