package com.tqx.design.observe;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 17:15
 */
public class MessageBPublisher implements Publisher {
    @Override
    public void messageSend(String weather) {
        System.out.println("当前天气已变为：" + weather + ",不适宜出门");
    }
}
