package com.tqx.design.factory_strategy.ann;

import java.lang.annotation.*;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/22 8:21
 */
@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
public @interface Inject {

    String name() default "";

}
