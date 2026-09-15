package com.tqx.design.observe;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 16:59
 */
public class MessagePublisher implements Publisher {

    @Override
    public void messageSend(String weather) {
        System.out.println("当前天气已变为：" + weather);
    }
}
