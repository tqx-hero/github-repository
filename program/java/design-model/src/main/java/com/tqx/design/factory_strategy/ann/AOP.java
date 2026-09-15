package com.tqx.design.factory_strategy.ann;

import java.lang.annotation.*;

/**
 * 需要对类进行AOP的注解
 */
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@Inject
public @interface AOP {

    String value() default "";

    boolean enhance() default true;
}
