package com.tqx.graalvm.aop;

import com.tqx.graalvm.ann.Permission;
import com.tqx.graalvm.enums.Permissions;
import com.tqx.graalvm.exception.ExceptionResolver;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

import java.util.Arrays;
import java.util.concurrent.atomic.AtomicBoolean;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 8:55
 */
@Component
@Aspect
public class ServiceAOP {

    @Pointcut(value = "@within(com.tqx.graalvm.ann.Permission)")
    public void pointCut() {

    }

    @Before("pointCut()")
    public void before(JoinPoint joinPoint) throws Exception {
        Permission permission = joinPoint.getTarget().getClass().getAnnotation(Permission.class);
        if (permission == null) {
            throw new ExceptionResolver(400, "没有访问权限.");
        }
        Permissions[] p = permission.permission();
        AtomicBoolean config = new AtomicBoolean(false);
        if (!(p == null || p.length == 0)) {
            String methodName = joinPoint.getSignature().getName();
            if (methodName.equals(Permissions.SELECT.getName()))
                config.set(true);
            else {
                Arrays.stream(p).forEach(x -> {
                    if (x.getName().equals(methodName)) {
                        config.set(true);
                    }
                });
            }
            if (!config.get()) {
                throw new ExceptionResolver(400, "没有访问权限.");
            }
        }
    }

}
