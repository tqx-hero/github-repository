package com.tqx.design.factory_strategy.util;

import java.lang.annotation.*;
import java.util.Objects;

/**
 * @author Administrator
 * @version 1.0
 * @description: 判断类是否存在注解或该注解的派生注解
 * @date 2026/3/22 7:57
 */
public class AnnotationUtils {

    /**
     * 判断该类是否存在注解/派生注解
     * 当前作用域仅支持类
     *
     * @param clazz
     * @param annotation
     * @return
     */
    public static boolean contaions(Class clazz, Class annotation) {
        return Objects.nonNull(clazz.getAnnotation(annotation))
                || contaionsMetaAnnotation(clazz.getAnnotations(), annotation, null, null);
    }

    /**
     * 判断该类有无注解/派生注解，以及相关属性值是否与预期值相同
     * 当前作用域仅支持类
     *
     * @param clazz      类
     * @param annotation 注解
     * @return
     * @methedName methedName 方法名
     * @expectVal expectVal 预期值
     */
    public static boolean contaions(Class clazz, Class annotation, String methedName, Object expectVal) {
        return contaionsMetaAnnotation(clazz.getAnnotations(), annotation, methedName, expectVal);
    }


    private static boolean isBasicMetaAnnotation(Annotation ann) {

        return ann.annotationType() == Target.class
                || ann.annotationType() == Documented.class
                || ann.annotationType() == Retention.class
                || ann.annotationType() == Inherited.class
                || ann.annotationType() == Repeatable.class;
    }

    private static boolean contaionsMetaAnnotation(Annotation[] annotations, Class ann, String param, Object paramVal) {
        if (Objects.isNull(annotations) || annotations.length == 0) {
            return false;
        }
        for (Annotation at : annotations) {
            //忽略5个基本元注解
            if (isBasicMetaAnnotation(at)) {
                continue;
            }
            if (at.annotationType() == ann) {
                try {
                    return Objects.isNull(param) ||
                            Objects.deepEquals(at.annotationType()
                                    .getDeclaredMethod(param)
                                    .getDefaultValue(), paramVal);
                } catch (NoSuchMethodException e) {
                    throw new RuntimeException(e);
                }
            }
            return contaionsMetaAnnotation(at.annotationType().getAnnotations(), ann, param, paramVal);
        }
        return false;
    }

//    public static void main(String[] args) {
//        System.out.println(contaions(WolmaStrategy.class, Inject.class));
//    }

}
