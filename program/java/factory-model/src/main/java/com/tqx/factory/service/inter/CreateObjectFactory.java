package com.tqx.factory.service.inter;

import java.lang.reflect.InvocationTargetException;

public interface CreateObjectFactory extends BeanFactoryDefine {
    <T> T getObject(Class<T> classType) throws Exception;

    <T> T getObject(Class<T> classType, Object... args) throws Exception;
}
