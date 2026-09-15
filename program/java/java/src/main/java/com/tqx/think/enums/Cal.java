package com.tqx.think.enums;

/**
 * @author Administrator
 * @version 1.0
 * @description: 枚举类中定义抽象方法
 * @date 2026/4/10 18:14
 */
public enum Cal {

    PLUS {
        @Override
        public int calculate(int a, int b) {
            return a + b;
        }
    };

    public abstract int calculate(int a, int b);
}
