package com.spring.importclass.selector;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.context.properties.bind.Binder;
import org.springframework.context.EnvironmentAware;
import org.springframework.context.annotation.ImportSelector;
import org.springframework.core.env.Environment;
import org.springframework.core.type.AnnotationMetadata;

import java.util.Arrays;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: 通过实现ImportSelector，EnvironmentAware接口，获取配置文件中的信息动态加载所需要的配置文件
 * @date 2026/3/9 8:31
 */
public class MyImportSelector implements ImportSelector, EnvironmentAware {

    private Environment environment;

    @Override
    public String[] selectImports(AnnotationMetadata importingClassMetadata) {
        List list = Binder.get(environment).bind("my.selects.list", List.class)
                .orElse(List.of());
        return (String[]) list.toArray(new String[list.size()]);
    }

    @Override
    public void setEnvironment(Environment environment) {
        this.environment = environment;
    }
}
