package com.spring.importclass.bean;


import com.spring.importclass.dao.UserDao;
import com.spring.importclass.service.UserService;
import org.springframework.beans.factory.support.BeanDefinitionRegistry;
import org.springframework.beans.factory.support.RootBeanDefinition;
import org.springframework.context.annotation.ImportBeanDefinitionRegistrar;
import org.springframework.core.type.AnnotationMetadata;

/**
 * @author Administrator
 * @version 1.0
 * @description: 通过实现ImportBeanDefinitionRegistrar，新建RootBeanDefinition，手动将要注入的类放入注册器里
 * @date 2026/3/9 9:03
 */
public class MyBeanDefinition implements ImportBeanDefinitionRegistrar {
    @Override
    public void registerBeanDefinitions(AnnotationMetadata importingClassMetadata, BeanDefinitionRegistry registry) {

        RootBeanDefinition definition = new RootBeanDefinition(UserService.class);
        RootBeanDefinition definition2 = new RootBeanDefinition(UserDao.class);
        registry.registerBeanDefinition("userService", definition);
        registry.registerBeanDefinition("userDao", definition2);
    }
}
