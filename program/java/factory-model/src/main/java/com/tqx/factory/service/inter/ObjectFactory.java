package com.tqx.factory.service.inter;


/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 15:37
 */
public class ObjectFactory implements CreateObjectFactory {

    @Override
    public <T> T getObject(Class<T> classType) throws Exception {
        System.out.println("创建==" + classType + "实例");
        return classType.getConstructor().newInstance();
    }

    @Override
    public <T> T getObject(Class<T> classType, Object... args) throws Exception {
        if (args.length == 0) {
            return newInstance(classType);
        }
        System.out.println("有参实例创建");
        Class[] parameterTypes = new Class[args.length];
        for (int i = 0; i < args.length; i++) {
            parameterTypes[i] = args[i].getClass();
        }
        return classType.getConstructor(parameterTypes).newInstance(args);
    }

    public static <T> T newInstance(Class<T> classType) throws Exception {
        return new ObjectFactory().getObject(classType);
    }

    public static <T> T newInstance(Class<T> classType, Object... args) throws Exception {
        if (args.length == 0) {
            return newInstance(classType);
        }
        return new ObjectFactory().getObject(classType, args);
    }


}
