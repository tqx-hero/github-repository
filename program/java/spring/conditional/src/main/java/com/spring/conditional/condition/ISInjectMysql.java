package com.spring.conditional.condition;

import org.springframework.context.annotation.Condition;
import org.springframework.context.annotation.ConditionContext;
import org.springframework.core.type.AnnotatedTypeMetadata;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/9 11:50
 */
public class ISInjectMysql implements Condition {
    @Override
    public boolean matches(ConditionContext context, AnnotatedTypeMetadata metadata) {
        return DBCondition.isMysql();
    }
}
