package com.tqx.factory.service.inter;

public interface BeanFactoryDefine {
        <T> T getObject(Class<T> classType) throws Exception;
}
