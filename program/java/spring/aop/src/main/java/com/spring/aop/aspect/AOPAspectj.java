package com.spring.aop.aspect;

import com.spring.aop.cache.CacheLogs;
import com.spring.aop.cache.entry.LogsEntry;
import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.reflect.MethodSignature;
import org.springframework.stereotype.Component;

import java.lang.reflect.Method;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 17:44
 */
//@Component
//@Aspect
public class AOPAspectj {


    @Pointcut("@annotation(Logs)")
    public void pointCut() {
    }
//
//    @Pointcut("@annotation(log)")
//    public void pointCuts(Logs log) {
//    }

    @Before("pointCut()")
    public void initLogs(JoinPoint joinPoint) {
        MethodSignature signature = (MethodSignature) joinPoint.getSignature();
        Method method = signature.getMethod();
        CacheLogs.getMethodLogs(method);
        CacheLogs.getClassLogs(joinPoint.getTarget().getClass());
    }

    @Around("pointCut()")
    public Object doAnn(ProceedingJoinPoint joinPoint) {
        System.out.println("类名=====" + joinPoint.getTarget());
        Object proceed;
        MethodSignature signature = (MethodSignature) joinPoint.getSignature();
        Method method = signature.getMethod();
        LogsEntry logsEntry = CacheLogs.getMethodLogs(method);
        System.out.println("类注解信息===" + logsEntry.getValue());
        LogsEntry classLogs = CacheLogs.getClassLogs(joinPoint.getTarget().getClass());
        System.out.println("方法注解信息===" + classLogs.getValue());
        try {
            proceed = joinPoint.proceed();
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
        return proceed;
    }
}
