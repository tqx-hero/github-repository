package com.tqx.factory.entity;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 15:47
 */
public class UserVO {

    private String name;

    private Integer age;

    public UserVO(Integer age, String name) {
        this.age = age;
        this.name = name;
    }

    @Override
    public String toString() {
        return "UserVO{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }

    public Integer getAge() {
        return age;
    }

    public void setAge(Integer age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public UserVO() {
    }
}
