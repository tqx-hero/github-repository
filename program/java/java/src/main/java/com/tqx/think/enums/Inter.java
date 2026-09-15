package com.tqx.think.enums;

import com.tqx.think.IInter;

/**
 * @author Administrator
 * @version 1.0
 * @description: 枚举类实现接口
 * @date 2026/4/10 18:18
 */
public enum Inter implements IInter {
    SUCCESS(200),
    FAIL(404);

    Inter(int code) {
        this.code = code;
    }


    @Override
    public int getCode() {
        return code;
    }

    private int code;
}
