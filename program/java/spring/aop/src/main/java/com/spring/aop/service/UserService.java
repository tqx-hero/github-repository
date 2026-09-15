package com.spring.aop.service;

import com.spring.aop.aspect.Logs;
import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 14:16
 */
@Component
@Logs("用户service")
public class UserService implements IUserservice {

    //实现基础的增删改查
    public void add() {
        System.out.println("执行add操作");
    }

    public Object delete() {
        System.out.println("delete");
        throw new RuntimeException("出错啦");
    }

    @Logs("update")
    public int update(int i) {
        System.out.println("操作。。update");
        return i;
    }

    public void query() {
        System.out.println("query");
    }
}
