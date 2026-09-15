package com.tqx.design.observe;

import java.util.ServiceLoader;

/**
 * @author Administrator
 * @version 1.0
 * @description: 观察者模式
 * @date 2026/3/25 17:02
 */
public class Test {

    public static void main(String[] args) {
        ServiceLoader<Publisher> publishers = ServiceLoader.load(Publisher.class);
        IWeatherInternation controller = new WeatherController();
        //订阅者订阅消息
        publishers.forEach(controller::addPublisher);

        //天气有变化，自动发送通知给订阅者
        controller.weatherChange("大雪");

    }


}
