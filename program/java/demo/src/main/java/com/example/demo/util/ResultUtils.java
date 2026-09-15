package com.example.demo.util;


import com.example.demo.entity.Result;
import com.example.demo.entity.StatusCode;

/**
 * @author tqx
 * @description 返回结果utils
 * @date 2020-12-28 14:44
 */
public class ResultUtils<T> implements ResponseUtils<T> {

    /******************************SUCCESS *************************************/
    /**
     * 返回成功
     *
     * @param o 返回的结果
     * @return
     */
    public  static <T> Result<T> success(T o) {
        return success(StatusCode.SUCCESS, o);
    }

    /**
     * 返回成功
     *
     * @return
     */
    public static <T> Result<T> success() {
        return success(StatusCode.SUCCESS);
    }

    /**
     * 返回成功
     *
     * @param enums 枚举实体
     * @return
     */
    public static <T> Result<T> success(StatusCode enums) {
        return success(enums, null);
    }

    /**
     * 返回成功
     *
     * @param enums 枚举实体
     * @param obj   返回的结果
     * @return
     */
    public static <T> Result<T> success(StatusCode enums, T obj) {
        return resposne(enums.isSuccess(),enums.getCode(), enums.getMsg(), obj);
    }


    /******************************FAILURE *************************************/

    /**
     * 返回失败
     *
     * @param msg 失败信息
     * @return
     */
    public static <T>Result<T> failure(String msg) {
        return failure(StatusCode.FAIL.getCode(), msg);
    }

    /**
     * 返回失败
     *
     * @return
     */
    public static <T> Result<T> failure() {
        return failure(StatusCode.FAIL.getMsg());
    }

    /**
     * 返回失败
     *
     * @param code 状态码
     * @param msg  失败信息
     * @return
     */
    public static <T> Result<T> failure(Integer code, String msg) {
        return resposne(false,code, msg, null);
    }


    /**
     * 返回失败
     *
     * @param enums 枚举实例
     * @return
     */
    public static <T> Result<T> failure(StatusCode enums) {
        return failure(enums, null);
    }

    /**
     * 返回失败
     *
     * @param enums 枚举实例
     * @param obj   结果实体
     * @return
     */
    public static <T> Result<T> failure(StatusCode enums, T obj) {
        return resposne(enums.isSuccess(), enums.getCode(), enums.getMsg(), obj);
    }

    /******************************OTHERS *************************************/


    /**
     * 自定义返回结果
     *
     * @param flag   是否成功
     * @param code   状态码
     * @param msg    返回消息
     * @param object 返回实体
     * @return
     * @author tqx
     * @date 2020-12-28 15:43:19
     **/
    public static <T> Result<T> resposne(boolean flag, Integer code, String msg, T object) {
        return new ResultUtils<T>().response(flag, code, msg, object);
    }
}
