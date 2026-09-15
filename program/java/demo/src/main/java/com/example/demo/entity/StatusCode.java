package com.example.demo.entity;

import lombok.AllArgsConstructor;
import lombok.Getter;
import org.springframework.http.HttpStatus;

/**
 * @author zy
 * @description
 * @date 2020/12/16 16:12
 */
@Getter
@AllArgsConstructor
public enum StatusCode {

    SUCCESS(true, HttpStatus.OK.value(), "操作成功"),
    FAIL(false, -1, "操作失败"),
    EXCEPTION(false, HttpStatus.BAD_REQUEST.value(), "出现异常"),
    ERROR(false, HttpStatus.INTERNAL_SERVER_ERROR.value(), "出现错误"),
    VALIDATE_FAILED(false, 404, "参数检验失败"),
    UNAUTHORIZED(false, 401, "暂未登录或token已经过期"),
    FORBIDDEN(false, 403, "没有相关权限");
    /**
     * =是否成功
     **/
    private boolean success;
    private Integer code;
    private String msg;
}
