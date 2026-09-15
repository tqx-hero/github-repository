package com.example.demo.util;

import com.example.demo.entity.Result;

/**
 * @author tqx
 * @description 返回结果集
 * @date 2020-12-28 15:21
 */
public interface ResponseUtils<T> {


    /**
     * 自定义返回结果
     *
     * @param code   状态码
     * @param msg    返回消息
     * @param o 返回实体
     * @return
     * @author tqx
     * @date 2020-12-28 15:43:19
     **/
    default Result<T> response(boolean flag, Integer code, String msg, T o) {
        return new Result<>(flag, code, msg, o);
    }

}
