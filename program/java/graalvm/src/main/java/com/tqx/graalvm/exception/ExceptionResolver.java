package com.tqx.graalvm.exception;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/12 9:44
 */
public class ExceptionResolver extends Exception {

    private Integer code;
    private String message;

    public ExceptionResolver(Integer code, String message) {
        this.code = code;
        this.message = message;
    }

    public Integer getCode() {
        return code;
    }

    public void setCode(Integer code) {
        this.code = code;
    }

    public void setMessage(String message) {
        this.message = message;
    }

    @Override
    public String getMessage() {
        return message;
    }
}
