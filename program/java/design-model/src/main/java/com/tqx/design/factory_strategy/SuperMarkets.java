package com.tqx.design.factory_strategy;

public enum SuperMarkets {
    WOLNA("wolmaStrategy"),
    YINZUO("yinzuoStrategy");


    SuperMarkets(String serviceName) {
        this.serviceName = serviceName;
    }

    public String get() {
        return serviceName;
    }

    private final String serviceName;

}
