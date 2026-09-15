package com.tqx.design.observe;

import java.util.ArrayList;
import java.util.List;

/**
 * @author Administrator
 * @version 1.0
 * @description: TODO
 * @date 2026/3/25 16:43
 */
public class WeatherController implements IWeatherInternation {

    //收集发布者集合，当数据变化时进行发送
    private static final List<Publisher> PUBLISHERS;

    private String weather = "晴天";

    static {
        PUBLISHERS = new ArrayList<>(32);
    }

    private void setWeather(String weather) {
        this.weather = weather;
    }

    @Override
    public void removePublisher(Publisher publisher) {
        PUBLISHERS.remove(publisher);
    }

    @Override
    public void addPublisher(Publisher publisher) {
        PUBLISHERS.add(publisher);
    }

    @Override
    public void weatherChange(String weather) {
        setWeather(weather);
        tellPublisher();
    }

    void tellPublisher() {
        PUBLISHERS.forEach(p -> p.messageSend(weather));
    }
}
