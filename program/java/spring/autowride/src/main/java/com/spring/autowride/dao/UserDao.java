package com.spring.autowride.dao;

import lombok.Data;
import org.springframework.stereotype.Repository;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 16:15
 */
@Repository
@Data
public class UserDao implements IUserDao {

    private String name;

    @Override
    public String toString() {
        return "UserDao{" +
                "name='" + name + '\'' +
                '}';
    }

    public UserDao() {
        name = "张三";
        System.out.println("UserDao constructor");
    }
}
