package com.tqx.graalvm.ann;


import com.tqx.graalvm.enums.Permissions;

import java.lang.annotation.*;

@Target({ElementType.TYPE})
@Retention(RetentionPolicy.RUNTIME)
@Documented
@Inherited
public @interface Permission {
    String value() default "";

    Permissions[] permission() default {};
}
