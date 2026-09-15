package com.spring.c3.dao;

import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Repository;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/7 21:10
 */
@Repository
//@Primary
public class UserDao implements IUserDao {

     String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String toString() {
        return "UserDao{" +
                "name='" + name + '\'' +
                '}';
    }

    @Override
    public void say() {
        System.out.println("hll");
    }

}
