package com.tqx.spring.processor;

import org.springframework.beans.BeansException;
import org.springframework.beans.factory.config.BeanPostProcessor;
import org.springframework.context.annotation.EnableAspectJAutoProxy;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 18:43
 */
@Component
public class ServicePostProcessor implements BeanPostProcessor {

    public ServicePostProcessor() {
        System.out.println("processor初始化");
    }

    @Override
    public Object postProcessAfterInitialization(Object bean, String beanName) throws BeansException {
        if (beanName.equals("serviceDao") || beanName.equals("servicePostProcessor") || beanName.equals("springConfig")) {
            System.out.println(beanName + " after");
        }
        return BeanPostProcessor.super.postProcessAfterInitialization(bean, beanName);
    }

    @Override
    public Object postProcessBeforeInitialization(Object bean, String beanName) throws BeansException {
        if (beanName.equals("serviceDao") || beanName.equals("servicePostProcessor") || beanName.equals("springConfig")) {
            System.out.println(beanName + " before");
        }
        return BeanPostProcessor.super.postProcessBeforeInitialization(bean, beanName);
    }
}
