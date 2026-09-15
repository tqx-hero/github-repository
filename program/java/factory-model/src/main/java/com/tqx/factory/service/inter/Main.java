package com.tqx.factory.service.inter;

import com.tqx.factory.entity.UserVO;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 15:47
 */
public class Main {

    public static void main(String[] args) throws Exception {

        String name = "张三";
        Integer age = 18;
//        CreateObjectFactory factory = () -> new UserVO(age, name);

        UserVO vo = ObjectFactory.newInstance(UserVO.class);
        vo.setAge(age);
        vo.setName(name);
        System.out.println(vo);

        System.out.println(ObjectFactory.newInstance(UserVO.class, age, name));
    }
}
