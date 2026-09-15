package com.tqx.design.observe;

public interface IWeatherInternation {

    void removePublisher(Publisher publisher);

    void addPublisher(Publisher publisher);

    void weatherChange(String weather);

}
