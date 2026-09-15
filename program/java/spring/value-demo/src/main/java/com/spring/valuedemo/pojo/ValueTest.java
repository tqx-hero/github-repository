package com.spring.valuedemo.pojo;

import lombok.Data;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Map;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 19:02
 */
@Component
public class ValueTest {

    @Value("${value.name:李四}")
    private String name;
    @Value("${value.age}")
    private int age;

//    @Value("#{'${value.hobby}'.split(',')}")
    private List<String> list;

    private Map<String,Integer> map;

    @Override
    public String toString() {
        return "ValueTest{" +
                "age=" + age +
                ", name='" + name + '\'' +
                ", list=" + list +
                ", map=" + map +
                '}';
    }

    public List<String> getList() {
        return list;
    }

    public void setList(List<String> list) {
        this.list = list;
    }

    public Map<String, Integer> getMap() {
        return map;
    }

    public void setMap(Map<String, Integer> map) {
        this.map = map;
    }

    public int getAge() {
        return age;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }


}
