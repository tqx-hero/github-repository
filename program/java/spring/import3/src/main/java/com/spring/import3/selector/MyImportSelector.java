package com.spring.import3.selector;

import org.springframework.context.annotation.ImportSelector;
import org.springframework.core.type.AnnotationMetadata;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 13:59
 */
public class MyImportSelector implements ImportSelector {
    @Override
    public String[] selectImports(AnnotationMetadata importingClassMetadata) {
        return new String[]{
                "com.spring.import3.dao.UserDao",
                "com.spring.import3.service.UserService"
        };
    }
}
