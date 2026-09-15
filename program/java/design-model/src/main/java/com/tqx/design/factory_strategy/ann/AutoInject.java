package com.tqx.design.factory_strategy.ann;

import java.lang.annotation.*;

@Target({ElementType.FIELD})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
public @interface AutoInject {

    String value() default "";

}
