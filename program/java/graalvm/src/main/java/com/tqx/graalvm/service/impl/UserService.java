package com.tqx.graalvm.service.impl;

import com.tqx.graalvm.ann.Permission;
import com.tqx.graalvm.enums.Permissions;
import com.tqx.graalvm.service.IUserService;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 8:54
 */
@Service
@Permission
public class UserService implements IUserService {
    @Override
    public void say(String name) {
        System.out.println("UserService say:" + name);
    }

    @Override
    public void add(String name) {
        System.out.println("add:" + name);
    }

    @Override
    public void delete(String name) {
        System.out.println("delete:" + name);
    }

    @Override
    public void update(String name) {
        System.out.println("update:" + name);
    }

    @Override
    public void select(String name) {
        System.out.println("select:" + name);
    }


}
