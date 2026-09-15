package com.spring.factorybean;

import com.spring.factorybean.factory.ImplFactoryBean;
import com.spring.factorybean.service.CService;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ConfigurableApplicationContext;

@SpringBootApplication
public class FactoryBeanApplication {

    public static void main(String[] args) {
        ConfigurableApplicationContext run = SpringApplication.run(FactoryBeanApplication.class, args);

        //com.spring.factorybean.service.CService@511d5d04 ，获取的是getObject()方法返回的bean
        System.out.println(run.getBean("implFactoryBean"));
        //com.spring.factorybean.factory.ImplFactoryBean@682c1e93,相当于根据类型获取getBean(ImplFactoryBean.class)
        System.out.println(run.getBean("&implFactoryBean"));
        //com.spring.factorybean.factory.ImplFactoryBean@682c1e93
        System.out.println(run.getBean(ImplFactoryBean.class));
        //com.spring.factorybean.service.CService@682c1e93，通过修改implFactoryBean中getObjectType()返回值类型可以通过类型获取bean
        System.out.println(run.getBean(CService.class));
    }

}
