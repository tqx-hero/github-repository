package com.spring.factorybean.factory;

import com.spring.factorybean.service.CService;
import org.jspecify.annotations.Nullable;
import org.springframework.beans.factory.FactoryBean;
import org.springframework.stereotype.Component;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/8 14:17
 */
@Component
public class ImplFactoryBean implements FactoryBean {

    //可以在ImplFactoryBean注入spring容器时多注入一个bean，这个bean可以通过获取implFactoryBean名的形式来获得，若重写getObjectType()后，也可以通过CService.class类型获取
    @Override
    public @Nullable Object getObject() throws Exception {
        return new CService();
    }

    //重写该方法可以让CService()通过类型来获取，不重写只能通过implFactoryBean名称获取
    @Override
    public @Nullable Class<?> getObjectType() {
        return CService.class;
    }
}
