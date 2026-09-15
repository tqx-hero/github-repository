package com.spring.import4.bean;

import com.spring.import4.dao.UserDao;
import com.spring.import4.service.CService;
import org.springframework.beans.factory.support.BeanDefinitionRegistry;
import org.springframework.beans.factory.support.RootBeanDefinition;
import org.springframework.context.annotation.ImportBeanDefinitionRegistrar;
import org.springframework.core.type.AnnotationMetadata;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 14:04
 */
public class MyBeanDefinition implements ImportBeanDefinitionRegistrar {
    @Override
    public void registerBeanDefinitions(AnnotationMetadata importingClassMetadata, BeanDefinitionRegistry registry) {
        RootBeanDefinition definition = new RootBeanDefinition(UserDao.class);
        RootBeanDefinition definition1 = new RootBeanDefinition(CService.class);
        registry.registerBeanDefinition("userDao", definition);
        registry.registerBeanDefinition("cService", definition1);
    }
}
