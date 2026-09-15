package com.spring.aop.aspect;

import org.aspectj.lang.JoinPoint;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.*;
import org.springframework.aop.support.AopUtils;
import org.springframework.stereotype.Component;

import java.util.Arrays;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/10 14:35
 */
@Aspect
@Component
public class LogAspect {


    @Pointcut("execution(* com.spring.aop..*Service.*(..))")
    public static void pointCut() {

    }

    @AfterThrowing(value = "pointCut()",
            throwing = "e")
    public void exception(JoinPoint joinPoint, Exception e) {
        System.out.println("异常通知");
        System.out.println("异常信息：" + e.getMessage());
    }

    @AfterReturning(value = "pointCut()",
            returning = "result")
    public void returns(JoinPoint jo, Object result) throws Throwable {

    }


    @Around("pointCut()")
    public Object log(ProceedingJoinPoint jo) {

        Object proceed;
        try {
            System.out.println("代理=" + jo.getThis().getClass().getName());
            System.out.println("目标=" + jo.getTarget().getClass().getName());
            proceed = jo.proceed();
            System.out.println("返回值：" + proceed);
        } catch (Throwable e) {
            throw new RuntimeException(e);
        }
        return proceed;
    }

    @After("pointCut()")
    public void after(JoinPoint jo) {
        System.out.println("后置通知");
    }

    @Before("pointCut()")
    public void me1(JoinPoint joinPoint) {
        System.out.println("前置通知");
//        System.out.println("方法名=" + joinPoint.getSignature().getName());
//        System.out.println("参数列表==" + Arrays.toString(joinPoint.getArgs()));
//        System.out.println("目标对象===" + joinPoint.getTarget());
    }

}
