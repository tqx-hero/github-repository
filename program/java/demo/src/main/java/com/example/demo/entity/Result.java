package com.example.demo.entity;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.io.Serializable;

/**
 * @author zy
 * @description
 * @date 2020/12/16 15:51
 */
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Result<T> implements Serializable {

    private static final long serialVersionUID = 3383953825056233422L;
    /**
     * =是否成功
     **/
    private boolean success;

    /**
     * 状态码
     */
    private Integer code;

    /**
     * 返回提示信息
     */
    private String msg;

    /**
     * 返回的数据
     */
    private T data;

}
