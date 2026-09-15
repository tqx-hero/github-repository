package com.tqx.design.factory_strategy;

import com.tqx.design.factory_strategy.ann.Inject;

import java.lang.annotation.*;

@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
@Inject
public @interface SuperMarket {
    String name() default "";
}
